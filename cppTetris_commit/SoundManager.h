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
     {"story1", "../music/_���丮-����_.wav"},
     {"story2", "../music/_���丮-����-2_.wav"},
     {"elevator", "../music/��������-�ö󰡴�_.wav"},
     {"floor5", "../music/_5��_.wav"},
     {"floor6", "../music/_6��_.wav"},
     {"stairs", "../music/_6��-1_.wav"},
     {"final1", "../music/_6��-2_.wav"},
     {"floor2", "../music/_���_.wav"},
     {"floor1", "../music/_1��_.wav"},
     {"floor1_return", "../music/Undertale_OST_1��.wav"},
     {"final2", "../music/������2.wav"}
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
