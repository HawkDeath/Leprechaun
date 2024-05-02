#define VK_NO_PROTOTYPES

#include <vulkan/vulkan.h>
#include <volk/volk.h>
#include "Render/gapi_vk/VulkanApiDevice.h"

#include "Window/Window.h"
#include "Log/Log.h"

#include <set>
#include <vector>
#include <string>

// TODO: resolve this in another way
const std::vector<const char *> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

namespace Leprechaun {
    VulkanApiDevice::VulkanApiDevice(Window &win) : m_window{win} {
        VkResult vulkan_loader = volkInitialize();
        if (vulkan_loader != VK_SUCCESS) { RT_THROW("Failed to load vulkan driver"); }
        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pNext = VK_NULL_HANDLE;
        appInfo.apiVersion = VK_MAKE_VERSION(1, 3, 0);
        appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
        appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
        appInfo.pApplicationName = "Leprechaun_app";
        appInfo.pEngineName = "Leprechaun_engine";

        VkInstanceCreateInfo instanceCreateInfo = {};
        instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceCreateInfo.pNext = VK_NULL_HANDLE;
        instanceCreateInfo.flags = 0u;
        instanceCreateInfo.pApplicationInfo = &appInfo;
        instanceCreateInfo.enabledLayerCount = 0u;


        auto extensions_name = m_window.get_vk_extensions();
        instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(extensions_name.size());
        instanceCreateInfo.ppEnabledExtensionNames = extensions_name.data();

        VK_CHECK(vkCreateInstance(&instanceCreateInfo, nullptr, &m_instance), "Failed to create VkInstance");
        volkLoadInstance(m_instance);


        uint32_t physicalDeviceCount = 0u;
        vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, nullptr);
        if (physicalDeviceCount == 0u) { RT_THROW("Not found gpu supported Vulkan API"); }

        std::vector<VkPhysicalDevice> gpus(physicalDeviceCount);
        vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, gpus.data());
        LOG("Found {} gpu(s)", physicalDeviceCount);

        for (auto &gpu: gpus) {
            VkPhysicalDeviceProperties props;
            vkGetPhysicalDeviceProperties(gpu, &props);
            if (props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
                LOG("Chosen \'{}\'", props.deviceName);
                m_physical_device = gpu;
                break;
            }
        }
        if (m_physical_device == VK_NULL_HANDLE) {
            m_physical_device = gpus[0];
            vkGetPhysicalDeviceProperties(m_physical_device, &device_properties);
            LOG("Chosen \'{}\'", device_properties.deviceName);
        }

        // Create surface
        m_window.createVkSurface(m_instance, m_surface);

        VkPhysicalDeviceFeatures reqested_features = {};
        reqested_features.samplerAnisotropy = VK_TRUE;

        // get all families queues
        uint32_t queueFamiliesCount = 0u;
        vkGetPhysicalDeviceQueueFamilyProperties(m_physical_device, &queueFamiliesCount, nullptr);
        if (queueFamiliesCount == 0u) { RT_THROW("Cannot find ANY validate queue on GPU"); }
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamiliesCount);
        vkGetPhysicalDeviceQueueFamilyProperties(m_physical_device, &queueFamiliesCount, queueFamilies.data());
        uint32_t graphics_family_queue_idx = 0u;
        uint32_t present_family_queue_idx = 0u;
        uint32_t compute_family_queue_idx = 0u;
        bool presentQueueHasBeenFound = false;
        for (uint32_t i = 0u; i < queueFamilies.size(); i++) {
            if (!presentQueueHasBeenFound)
            {
                VkBool32 presentSupported = false;

                vkGetPhysicalDeviceSurfaceSupportKHR(m_physical_device, i, m_surface, &presentSupported);
                if (presentSupported) {
                    families_queues.push_back(vk::QueueFamily{.type = vk::QueueType::Present, .index_family = i});
                    present_family_queue_idx = i;
                }
                presentQueueHasBeenFound = true;
            }

            if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                families_queues.push_back(vk::QueueFamily{.type = vk::QueueType::Graphics, .index_family = i});
                graphics_family_queue_idx = i;
                continue;
            }

            if (queueFamilies[i].queueFlags & VK_QUEUE_COMPUTE_BIT) {
                families_queues.push_back(vk::QueueFamily{.type = vk::QueueType::Compute, .index_family = i});
                compute_family_queue_idx = i;
                continue;
            }
        }
        std::set<uint32_t> queues_ids = {graphics_family_queue_idx, present_family_queue_idx, compute_family_queue_idx};
        float prio = 1.0f;
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        for (auto &queue: queues_ids) {
            VkDeviceQueueCreateInfo queueCreateInfo = {};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueCount = 1u;
            queueCreateInfo.pQueuePriorities = &prio;
            queueCreateInfo.queueFamilyIndex = queue;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkDeviceCreateInfo deviceCreateinfo = {};
        deviceCreateinfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        deviceCreateinfo.pNext = VK_NULL_HANDLE;
        deviceCreateinfo.pEnabledFeatures = &reqested_features;
        deviceCreateinfo.pQueueCreateInfos = queueCreateInfos.data();
        deviceCreateinfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        deviceCreateinfo.ppEnabledExtensionNames = deviceExtensions.data();
        deviceCreateinfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());

        VK_CHECK(vkCreateDevice(m_physical_device, &deviceCreateinfo, nullptr, &m_device),
                 "Failed to create Vulkan Logical device");

        vkGetDeviceQueue(m_device, graphics_family_queue_idx, 0u, &m_graphics_queue);
        if (m_graphics_queue == VK_NULL_HANDLE) { RT_THROW("Failed to get graphcis queue handle"); }
        vkGetDeviceQueue(m_device, present_family_queue_idx, 0u, &m_present_queue);
        if (m_present_queue == VK_NULL_HANDLE) { RT_THROW("Failed to get present queue handle"); }
        vkGetDeviceQueue(m_device, compute_family_queue_idx, 0u, &m_compute_queue);
        if (m_compute_queue == VK_NULL_HANDLE) { RT_THROW("Failed to get compute queue handle"); }
    }

    VulkanApiDevice::~VulkanApiDevice() {
        vkDestroyDevice(m_device, nullptr);
        vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
        vkDestroyInstance(m_instance, nullptr);
    }

}