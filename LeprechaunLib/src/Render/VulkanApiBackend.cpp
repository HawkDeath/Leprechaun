#include "Render/VulkanApiBackend.h"
#include "Render/gapi_vk/VulkanApiDevice.h"

namespace Leprechaun
{
    ApiDevice* VulkanApiBackend::createDevice()
    {
        return new VulkanApiDevice();
    }

    void VulkanApiBackend::destroyDevice(ApiDevice* d)
    {
            delete d;
    }
}