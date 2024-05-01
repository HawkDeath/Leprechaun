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

        // TODO: maybe unique_ptr will be better then raw pointer
        ApiDevice* createDevice() override;
        void destroyDevice(ApiDevice* d) override;

    };
}

#endif //LEPRECHAUN_VULKANAPIBACKEND_H
