#ifndef LEPRECHAUN_VULKANAPIDEVICE_H
#define LEPRECHAUN_VULKANAPIDEVICE_H

#include "Render/ApiDevice.h"

#include <vulkan/vulkan.h>

#include <vector>
#include <optional>

namespace Leprechaun {
    class Window;
    namespace vk {
        enum class QueueType : uint32_t {
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
        VulkanApiDevice(Window &win);

        virtual ~VulkanApiDevice();

        VkQueue get_graphics_queue() const { return m_graphics_queue; }

        VkQueue get_present_queue() const { return m_present_queue; }

        VkQueue get_compute_queue() const { return m_compute_queue; }

        VkSurfaceKHR get_surface_handle() const { return m_surface; }

        VkPhysicalDeviceProperties device_properties;
        std::vector<vk::QueueFamily> families_queues;
    private:
        Window &m_window;
        VkInstance m_instance{};
        VkPhysicalDevice m_physical_device = VK_NULL_HANDLE;
        VkDevice m_device{};

        VkQueue m_graphics_queue = {VK_NULL_HANDLE};
        VkQueue m_present_queue = {VK_NULL_HANDLE};
        VkQueue m_compute_queue = {VK_NULL_HANDLE};
        VkSurfaceKHR m_surface = {VK_NULL_HANDLE};

    };
}

#endif //LEPRECHAUN_VULKANAPIDEVICE_H
