#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include "Audio.h"
#include "Logging.h"

namespace CPL {
    ma_engine AudioManager::engine;

    void AudioManager::Init() {
        if (ma_engine_init(nullptr, &engine) != MA_SUCCESS) {
            Logging::Log(2, "Failed to initialize audio engine!");
            exit(-1);
        }
    }

    void AudioManager::PlaySFX(const std::string& audioPath) {
        ma_engine_play_sound(&engine, audioPath.c_str(), nullptr);
    }


    void AudioManager::Close() {
        ma_engine_uninit(&engine);
    }
}
