#pragma once

#include "../resource.h"
#include "../../prerequisites.h"

#include <d3d11.h>

class Texture : public Resource
{
public:
    Texture(const wchar_t* full_path);
    ~Texture();

private:

    ID3D11Resource* texture = nullptr;
    ID3D11ShaderResourceView* shader_view = nullptr;

    friend class Device_Context;
};