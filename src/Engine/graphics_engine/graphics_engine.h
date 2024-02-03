#pragma once

#include <d3d11.h>

class Graphics_Engine {
public:
    Graphics_Engine();
    ~Graphics_Engine();
    bool init();
    bool release();

    static Graphics_Engine* get_engine();

    
private:
    ID3D11Device* device;
    D3D_FEATURE_LEVEL m_feature_level;
    // or Immediate Device Contact Spider
    ID3D11DeviceContext* m_device_context;
};