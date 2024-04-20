#ifndef LEPRECHAUN_DEVICE_H
#define LEPRECHAUN_DEVICE_H

#include "RenderApiBackendAbstraction.h"

#include <memory>

namespace Leprechaun
{

    class Device
    {
    public:
        explicit Device(RenderApiBackendAbstraction &api);
        ~Device();
        // Buffer createBuffer(...);,
        // Texture2D createTextre2D(...);

    private:
        RenderApiBackendAbstraction &renderApi;
        ApiDevice* device;
    };
}


#endif // LEPRECHAUN_DEVICE_H