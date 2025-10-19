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

    Audio AudioManager::LoadAudio(const std::string& audioPath) {
        return {audioPath};
    }

    void AudioManager::PlaySFX(const Audio& audio) {
        ma_engine_play_sound(&engine, audio.path.c_str(), nullptr);
    }

    void AudioManager::Close() {
        ma_engine_uninit(&engine);
    }
}
