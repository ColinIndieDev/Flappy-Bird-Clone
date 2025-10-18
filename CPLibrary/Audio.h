#pragma once
#include "miniaudio.h"
#include <string>
#include "CPL.h"

namespace CPL {
    class AudioManager {
    public:
        static void Init();
        static void PlaySFX(const std::string& audioPath);
        static void Close();
    private:
        static ma_engine engine;
    };
}