#pragma once
#include <Windows.h>
#include <mmsystem.h>
#include <string>
#include <unordered_map>
#pragma comment(lib, "winmm.lib")

class SoundManager {
private:
    int level;
    std::string levelKey;

    std::unordered_map<std::string, const char*> bgmMap = {
        {"s1", "_½ºÅä¸®-ÁøÇà_.wav"},
        {"s2", "_½ºÅä¸®-ÁøÇà-2_.wav"},
        {"e", "¿¤·¹¿¡ÅÍ-¿Ã¶ó°¡´Â_.wav"},
        {"5f", "_5Ãþ_.wav"},
        {"6f", "_6Ãþ_.wav"},
        {"6f-1", "_6Ãþ-1_.wav"},
        {"6f-2", "_6Ãþ-2_.wav"},
        {"str", "_°è´Ü_.wav"},
         {"1f", "_1Ãþ_.wav"},
        {"1f-U", "Undertale_OST_1Ãþ.wav"},
        {"final2", "¸¶Áö¸·2.wav"}
    };

    const char* levelKeys[11] = {
        "story1",
        "story2",
        "floor1",
        "elevator",
        "floor2",
        "floor5",
        "floor6",
        "stairs",
        "floor1_return",
        "final1",
        "final2"
    };



public:
    SoundManager() : level(0), levelKey("story1") {}

    void setLevel(int lvl) {
        if (lvl >= 0 && lvl < 11) {
            level = lvl;
            levelKey = levelKeys[lvl];
            playBGMByKey(levelKey);
        }
    }

    void playBGMByKey(const std::string& key) {
        auto it = bgmMap.find(key);
        if (it != bgmMap.end()) {
            PlaySoundA(it->second, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        }
    }

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
