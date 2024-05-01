#define VK_NO_PROTOTYPES

#include <vulkan/vulkan.h>
#include <volk/volk.h>
#include "Render/gapi_vk/VulkanApiDevice.h"


#include "Log/Log.h"

#include <vector>
#include <string>

// TODO: resolve this in another way
const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

namespace Leprechaun {
    VulkanApiDevice::VulkanApiDevice() {
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

        // get all extensions
        uint32_t extensionsCount = 0u;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionsCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, extensions.data());

        std::vector<char *> extensions_name(extensions.size());
        uint32_t i = 0u;
        for (auto &ext: extensions) {
            extensions_name[i] = new char[VK_MAX_EXTENSION_NAME_SIZE];
            std::strcpy(extensions_name[i], ext.extensionName);

            LOG("{}", extensions_name[i]);
            i++;
        }
        extensions.clear();

        instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(extensions_name.size());
        instanceCreateInfo.ppEnabledExtensionNames = extensions_name.data();

        VK_CHECK(vkCreateInstance(&instanceCreateInfo, nullptr, &m_instance), "Failed to create VkInstance");
        volkLoadInstance(m_instance);

        for (auto &ext_name: extensions_name) {
            delete ext_name;
        }
        extensions_name.clear();

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
        VkPhysicalDeviceFeatures reqested_features = {};
        reqested_features.samplerAnisotropy = VK_TRUE;

        // get all families queues
        uint32_t queueFamiliesCount = 0u;
        vkGetPhysicalDeviceQueueFamilyProperties(m_physical_device, &queueFamiliesCount, nullptr);
        if (queueFamiliesCount == 0u) { RT_THROW("Cannot find ANY validate queue on GPU"); }
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamiliesCount);
        vkGetPhysicalDeviceQueueFamilyProperties(m_physical_device, &queueFamiliesCount, queueFamilies.data());
        for (uint32_t i = 0; i < queueFamilies.size(); ++i)
        {
            if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT )
            {
                families_queues.push_back(vk::QueueFamily{ .type = vk::QueueType::Graphics, .index_family = i });
                VkBool32 presentSupported = false;
                // TODO: add surface support
                // vkGetPhysicalDeviceSurfaceSupportKHR(m_physical_device, i, surface, &presentSupported);
                if (presentSupported)
                    families_queues.push_back(vk::QueueFamily{ .type = vk::QueueType::Present, .index_family = i });

                continue;
            }

            if (queueFamilies[i].queueFlags & VK_QUEUE_COMPUTE_BIT )
            {
                families_queues.push_back(vk::QueueFamily{ .type = vk::QueueType::Compute, .index_family = i });
                continue;
            }

        }

        float prio = 1.0f;
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        for (auto &queue : families_queues)
        {
            VkDeviceQueueCreateInfo queueCreateInfo = {};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueCount = 1u;
            queueCreateInfo.pQueuePriorities = &prio;
            queueCreateInfo.queueFamilyIndex = queue.index_family.value();
            std::string strQueueType;
            if (queue.type == vk::QueueType::Graphics) strQueueType = "Graphics";
            if (queue.type == vk::QueueType::Compute) strQueueType = "Compute";
            if (queue.type == vk::QueueType::Present) strQueueType = "Present";
            LOG("Preparing queue for {}", strQueueType);
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

    }

    VulkanApiDevice::~VulkanApiDevice() {
        vkDestroyDevice(m_device, nullptr);
        vkDestroyInstance(m_instance, nullptr);
    }

}