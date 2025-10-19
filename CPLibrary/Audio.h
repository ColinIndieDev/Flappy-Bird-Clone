#pragma once
#include <map>

#include "miniaudio.h"
#include <string>
#include "CPL.h"

namespace CPL {
    struct Audio {
        const std::string path;
    };

    class AudioManager {
    public:
        static void Init();
        static Audio LoadAudio(const std::string& audioPath);
        static void PlaySFX(const Audio& audio);
        static void Close();
    private:
        static ma_engine engine;
    };
}