#include "Render/VulkanApiBackend.h"
#include "Render/gapi_vk/VulkanApiDevice.h"

namespace Leprechaun
{
    VulkanApiBackend::VulkanApiBackend(Leprechaun::Window &win) : m_window{win} {}

    ApiDevice* VulkanApiBackend::createDevice()
    {
        return new VulkanApiDevice(m_window);
    }

    void VulkanApiBackend::destroyDevice(ApiDevice* d)
    {
            delete d;
    }
}