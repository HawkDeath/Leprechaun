#include "Render/Device.h"

namespace Leprechaun
{
    Device::Device(RenderApiBackendAbstraction &api) : renderApi{api} { device = renderApi.createDevice();}
    Device::~Device() {renderApi.destroyDevice(device);}

}