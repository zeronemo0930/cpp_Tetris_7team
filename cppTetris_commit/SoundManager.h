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
     {"story1", "../music/_½ºÅä¸®-ÁøÇà_.wav"},
     {"story2", "../music/_½ºÅä¸®-ÁøÇà-2_.wav"},
     {"elevator", "../music/¿¤·¹¿¡ÅÍ-¿Ã¶ó°¡´Â_.wav"},
     {"floor5", "../music/_5Ãþ_.wav"},
     {"floor6", "../music/_6Ãþ_.wav"},
     {"stairs", "../music/_6Ãþ-1_.wav"},
     {"final1", "../music/_6Ãþ-2_.wav"},
     {"floor2", "../music/_°è´Ü_.wav"},
     {"floor1", "../music/_1Ãþ_.wav"},
     {"floor1_return", "../music/Undertale_OST_1Ãþ.wav"},
     {"final2", "../music/¸¶Áö¸·2.wav"}
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
};
