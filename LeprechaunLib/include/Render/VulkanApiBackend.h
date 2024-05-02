#ifndef LEPRECHAUN_VULKANAPIBACKEND_H
#define LEPRECHAUN_VULKANAPIBACKEND_H

#include "RenderApiBackendAbstraction.h"

namespace Leprechaun
{
    class Window;
    class VulkanApiBackend : public RenderApiBackendAbstraction
    {
    public:
        explicit VulkanApiBackend(Window &win);
        virtual ~VulkanApiBackend() = default;

        // TODO: maybe unique_ptr will be better then raw pointer
        ApiDevice* createDevice() override;
        void destroyDevice(ApiDevice* d) override;
    private:
        Window &m_window;
    };
}

#endif //LEPRECHAUN_VULKANAPIBACKEND_H
