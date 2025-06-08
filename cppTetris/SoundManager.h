#pragma once
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

class SoundManager {
public:

    void playEffect(const char* filename) {
        PlaySoundA(filename, NULL, SND_FILENAME | SND_ASYNC);
    }

    void stopSound() {
        PlaySoundA(NULL, 0, 0);
    }

    void SetMasterVolume(float volume) {
        volume /= 100;
        // volume: 0.0f (0%) ~ 1.0f (100%)
        DWORD vol = DWORD(volume * 0xFFFF);
        DWORD both = (vol & 0xFFFF) | ((vol & 0xFFFF) << 16);
        waveOutSetVolume(NULL, both);
    }
};
