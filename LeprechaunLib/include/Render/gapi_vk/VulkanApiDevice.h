#ifndef LEPRECHAUN_VULKANAPIDEVICE_H
#define LEPRECHAUN_VULKANAPIDEVICE_H

#include "Render/ApiDevice.h"

namespace Leprechaun
{
    class VulkanApiDevice : public ApiDevice
    {
    public:
        VulkanApiDevice();
        virtual ~VulkanApiDevice();
    };
}

#endif //LEPRECHAUN_VULKANAPIDEVICE_H
