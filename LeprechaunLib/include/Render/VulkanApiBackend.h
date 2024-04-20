#ifndef LEPRECHAUN_VULKANAPIBACKEND_H
#define LEPRECHAUN_VULKANAPIBACKEND_H

#include "RenderApiBackendAbstraction.h"

namespace Leprechaun
{
    class VulkanApiBackend : public RenderApiBackendAbstraction
    {
    public:
        explicit VulkanApiBackend() = default;
        virtual ~VulkanApiBackend() = default;

        ApiDevice* createDevice() override;
        void destroyDevice(ApiDevice* d) override;

    };
}

#endif //LEPRECHAUN_VULKANAPIBACKEND_H
