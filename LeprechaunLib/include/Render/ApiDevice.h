#ifndef LEPRECHAUN_APIDEVICE_H
#define LEPRECHAUN_APIDEVICE_H

namespace Leprechaun
{
    class ApiDevice
    {
    public:
        ApiDevice() = default;
        virtual ~ApiDevice() = default;

        ApiDevice(const ApiDevice &) = delete;
        ApiDevice& operator=(const ApiDevice& ) = delete;

        ApiDevice(ApiDevice&&) = delete;
        ApiDevice& operator=(ApiDevice&&) = delete;


    };
}

#endif // LEPRECHAUN_APIDEVICE_H
