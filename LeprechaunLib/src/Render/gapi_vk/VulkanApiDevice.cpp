#include "Render/gapi_vk/VulkanApiDevice.h"
#include "Log/Log.h"
namespace Leprechaun
{
    VulkanApiDevice::VulkanApiDevice() { LOG("VulkanApiDevice {1}, {0}", "test", 23); }
    VulkanApiDevice::~VulkanApiDevice() noexcept = default;
}