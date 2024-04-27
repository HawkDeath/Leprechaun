#ifndef LEPRECHAUN_VULKANAPIDEVICE_H
#define LEPRECHAUN_VULKANAPIDEVICE_H

#include "Render/ApiDevice.h"

#include <vulkan/vulkan.h>

namespace Leprechaun
{
    class VulkanApiDevice : public ApiDevice
    {
    public:
        VulkanApiDevice();
        virtual ~VulkanApiDevice();

        VkPhysicalDeviceProperties device_properties;

    private:
        VkInstance m_instance{};
        VkPhysicalDevice m_physical_device = VK_NULL_HANDLE;
        VkDevice m_device{};
    };
}

#endif //LEPRECHAUN_VULKANAPIDEVICE_H
