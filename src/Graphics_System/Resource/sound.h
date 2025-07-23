#pragma once

#include <Audio.h>

#include "resource.h"
#include "resource_manager.h"
#include "../prerequisites.h"
#include <filesystem>
#include <../../../lib/miniaudio-master/miniaudio.h>

#include "../../Game/game_engine.h"



class Sound : public Resource
{
public:
    Sound(const wchar_t* sound_file_path, Resource_Manager* manager);
    ~Sound();

    void play(float volume);
    
private:
    
    const wchar_t* audio_file;

    static void data_callback(ma_device* p_device, void* p_output, const void* p_input, ma_uint32 frame_count);

    ma_result audio_result;
    ma_decoder audio_decoder;
    ma_device_config audio_device_config;
    ma_device audio_device;

    const wchar_t* sound_path;
};
