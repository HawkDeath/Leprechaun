#ifndef LEPRECHAUN_RENDERAPIBACKENDABSTRACTION_H
#define LEPRECHAUN_RENDERAPIBACKENDABSTRACTION_H

namespace Leprechaun
{
    class ApiDevice;
    class SwapChain;

    class RenderApiBackendAbstraction
    {
    public:
        // target api device, mean VulkanApiDevice, Dx12ApiDevice, etc..
        virtual ApiDevice* createDevice() = 0;
        virtual void destroyDevice(ApiDevice * device) = 0;
       // virtual SwapChain createSwapchain() = 0;
    };
}

#endif //LEPRECHAUN_RENDERAPIBACKENDABSTRACTION_H
