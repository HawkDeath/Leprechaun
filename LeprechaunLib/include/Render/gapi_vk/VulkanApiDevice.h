#ifndef LEPRECHAUN_VULKANAPIDEVICE_H
#define LEPRECHAUN_VULKANAPIDEVICE_H

#include "Render/ApiDevice.h"

#include <vulkan/vulkan.h>

#include <vector>
#include <optional>

namespace Leprechaun {
    namespace vk {
        enum class QueueType : uint8_t {
            Graphics,
            Compute,
            Present,
            Count
        };
        struct QueueFamily {
            QueueType type;
            std::optional<uint32_t> index_family;
        };
    }

    class VulkanApiDevice : public ApiDevice {
    public:
        VulkanApiDevice();

        virtual ~VulkanApiDevice();

        VkPhysicalDeviceProperties device_properties;

        std::vector<vk::QueueFamily> families_queues;
    private:
        VkInstance m_instance{};
        VkPhysicalDevice m_physical_device = VK_NULL_HANDLE;
        VkDevice m_device{};
    };
}

#endif //LEPRECHAUN_VULKANAPIDEVICE_H
