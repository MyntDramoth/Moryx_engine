#include "sound.h"


#define MINIAUDIO_IMPLEMENTATION
#include <../../../lib/miniaudio-master/miniaudio.h>

Sound::Sound(const wchar_t* sound_file_path, Resource_Manager* manager):Resource(sound_file_path,manager)
{
	const wchar_t* file_name = std::filesystem::path(sound_file_path).filename().wstring().data();
	auto extension = std::filesystem::path(sound_file_path).extension();


	if(!std::filesystem::exists(sound_file_path)) {
        MORYX_ERROR("File path is wrong or file does not exist!" << " || File name: " << file_name); 
    }
    audio_file = sound_file_path;
   
    ma_decoder_config decoder_config = ma_decoder_config_init_default();

    
    audio_result = ma_decoder_init_file_w(sound_file_path, NULL, &audio_decoder);
    if (audio_result != MA_SUCCESS) {
        MORYX_ERROR("failed to decode file! " << " || File name: " << file_name);
    }
    
    ma_device_config audio_device_config = ma_device_config_init(ma_device_type_playback);
    audio_device_config.playback.format   = audio_decoder.outputFormat;
    audio_device_config.playback.channels = audio_decoder.outputChannels;
    audio_device_config.sampleRate        = audio_decoder.outputSampleRate;
    audio_device_config.dataCallback      = data_callback;
    audio_device_config.pUserData         = &audio_decoder;

    audio_result = ma_device_init(NULL, &audio_device_config, &audio_device);
    if (audio_result != MA_SUCCESS) {
        ma_decoder_uninit(&audio_decoder);
        MORYX_ERROR("Failed to open playback device!")
    }

}

Sound::~Sound()
{
    ma_device_uninit(&audio_device);
    ma_decoder_uninit(&audio_decoder);
}

void Sound::play(float volume) {
	
	float pitch = 0.0f;
	float pan = 0.0f;
	
    audio_result = ma_device_start(&audio_device);
    if (audio_result != MA_SUCCESS) {
        ma_device_uninit(&audio_device);
        ma_decoder_uninit(&audio_decoder);
        MORYX_ERROR("Failed to start playback device");
    }
    
}

void Sound::data_callback(ma_device *p_device, void *p_output, const void *p_input, ma_uint32 frame_count) {
    ma_decoder* p_decoder = (ma_decoder*)p_device->pUserData;
    if (p_decoder == NULL) {
        //MORYX_ERROR("No decoder data!");
    }

    if(ma_decoder_read_pcm_frames(p_decoder, p_output, frame_count, NULL) != MA_SUCCESS) {
        //MORYX_ERROR("Failed to read decoder data!");
    }

    (void)p_input;
}