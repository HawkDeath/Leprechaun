#define  VK_NO_PROTOTYPES

#include <volk/volk.h>
#include "Render/gapi_vk/VulkanApiDevice.h"

#include "Log/Log.h"

#include <vector>
#include <string>

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

        for (auto &ext_name: extensions_name) {
            delete ext_name;
        }
        extensions_name.clear();

        uint32_t physicalDeviceCount = 0u;
        vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, nullptr);
        std::vector<VkPhysicalDevice> gpus(physicalDeviceCount);
        vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, gpus.data());
        if (gpus.empty()) { RT_THROW("Not found gpu supported Vulkan API"); }
        LOG("Found {} gpu(s)", physicalDeviceCount);

        for (auto &gpu: gpus) {
            VkPhysicalDeviceProperties props;
            vkGetPhysicalDeviceProperties(gpu, &props);
            if (props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
                LOG("Choosen {}", props.deviceName);
                m_physical_device = gpu;
                break;
            }
        }
        if (m_physical_device == VK_NULL_HANDLE) m_physical_device = gpus[0];

        VkDeviceCreateInfo deviceCreateinfo = {};
        deviceCreateinfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        deviceCreateinfo.pNext = VK_NULL_HANDLE;

        VK_CHECK(vkCreateDevice(m_physical_device, &deviceCreateinfo, nullptr, &m_device),
                 "Failed to create Vulkan Logical device");

    }

    VulkanApiDevice::~VulkanApiDevice() {
        vkDestroyInstance(m_instance, nullptr);
    }
}