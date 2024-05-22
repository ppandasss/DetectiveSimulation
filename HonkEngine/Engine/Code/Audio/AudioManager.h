#pragma once
#include <irrKlang/irrKlang.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

using namespace irrklang;

class AudioManager {
public:

    static AudioManager& GetInstance() {
        static AudioManager instance;
        return instance;
    }

    ~AudioManager() {
        // Clean up the sound engine
        for (auto& soundPair : playingSounds) {
            for (auto* sound : soundPair.second) {
                if (sound) {
                    sound->stop();
                    sound->drop(); 
                }
            }
        }
        engine->drop();
    }

    void LoadSound(const std::string& soundName, const std::string& filePath, float volume = 1.0f, float speed = 1.0f) 
    {
        std::cout << "Attempting to load sound: " << soundName << std::endl;
        auto it = sounds.find(soundName);
        if (it != sounds.end()) {
            engine->removeSoundSource(it->second);
        }

        ISoundSource* sound = engine->addSoundSourceFromFile(filePath.c_str());
        sounds[soundName] = sound;
        soundVolumes[soundName] = volume;
        soundSpeeds[soundName] = speed;

        std::cout << "Sound loaded: " << soundName << std::endl;

    }

   


    void PlaySound(const std::string& soundName, bool loop = false) {
        if (IsSoundPaused(soundName)) {
            ResumeSound(soundName); // Resume the sound if it's paused
        }
        else {
            auto it = sounds.find(soundName);
            if (it != sounds.end()) {
                ISound* sound = engine->play2D(it->second, loop, true, true);
                if (sound) {
                    sound->setVolume(soundVolumes[soundName]);
                    sound->setPlaybackSpeed(soundSpeeds[soundName]);
                    sound->setIsPaused(false);
                    playingSounds[soundName].push_back(sound);
                }
            }
        }
    }


    void PauseSound(const std::string& soundName) {
        auto it = playingSounds.find(soundName);
        if (it != playingSounds.end()) {
            for (auto& sound : it->second) {
                if (sound && !sound->isFinished() && !sound->getIsPaused()) {
                    sound->setIsPaused(true);
                }
            }
        }
    }

    void ResumeSound(const std::string& soundName) {
        auto it = playingSounds.find(soundName);
        if (it != playingSounds.end()) {
            for (auto& sound : it->second) {
                if (sound && sound->getIsPaused()) {
                    sound->setIsPaused(false);
                }
            }
        }
    }



    void StopSound(const std::string& soundName) {
        auto it = playingSounds.find(soundName);
        if (it != playingSounds.end()) {
            for (auto& sound : it->second) {
                if (sound && !sound->isFinished()) {
                    sound->stop();
                    sound->drop(); // Properly release the sound
                }
            }
            it->second.clear(); // Clear the list of sounds
            //std::cout << "Stopped sound: " << soundName << std::endl;
        }
    }

    bool IsSoundPaused(const std::string& soundName) {
        auto it = playingSounds.find(soundName);
        if (it != playingSounds.end()) {
            for (auto& sound : it->second) {
                if (sound && sound->getIsPaused()) {
                    return true;
                }
            }
        }
        return false;
    }


    void SetMasterVolume(float volume) {
        // Set the master volume (0.0 to 1.0)
        engine->setSoundVolume(volume);
    }

    void SetPlaybackSpeed(const std::string& soundName, float speed) {
        auto it = playingSounds.find(soundName);
        if (it != playingSounds.end()) {
            for (auto& sound : it->second) {
                if (sound && !sound->isFinished()) {
                    sound->setPlaybackSpeed(speed);
                }
            }
        }
    }

    bool IsSoundFinished(const std::string& soundName) {
        auto it = playingSounds.find(soundName);
        if (it != playingSounds.end()) {
            for (auto& sound : it->second) {
                if (sound && !sound->isFinished()) {
                    return false;
                }
            }
        }
        return true;
    }

    void SetSoundVolume(const std::string& soundName, float volume) {
        // Set the volume for a specific sound
        soundVolumes[soundName] = volume; // Update the volume in the map

        // Adjust the volume for all currently playing instances of this sound
        auto it = playingSounds.find(soundName);
        if (it != playingSounds.end()) {
            for (auto& sound : it->second) {
                if (sound && !sound->isFinished()) {
                    sound->setVolume(volume);
                }
            }
        }
    }

    bool IsSoundPlaying(const std::string& soundName) {
        auto it = playingSounds.find(soundName);
        if (it != playingSounds.end()) {
            for (auto& sound : it->second) {
                if (sound && !sound->isFinished()) {
                    return true; // Sound is currently playing
                }
            }
        }
        return false; // Sound is not playing
    }

private:

    AudioManager() {
        // Initialize the sound engine
        engine = createIrrKlangDevice();
        if (!engine) throw std::runtime_error("Could not create sound engine.");
    }

    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;
    ISoundEngine* engine;
    std::unordered_map<std::string, ISoundSource*> sounds;
    std::unordered_map<std::string, std::vector<ISound*>> playingSounds; // Tracks playing sounds
    std::unordered_map<std::string, float> soundVolumes; // New map for individual sound volumes
    std::unordered_map<std::string, float> soundSpeeds;
};
