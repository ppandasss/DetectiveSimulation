#pragma once
#include <irrKlang/irrKlang.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

using namespace irrklang;

enum SoundType {
    SFX,
    Music
};

class AudioManager {
public:
    static AudioManager& GetInstance() {
        static AudioManager instance;
        return instance;
    }

    ~AudioManager() {
        if (engine) {
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
    }

    void LoadSound(const std::string& soundName, const std::string& filePath, SoundType type, float volume = 1.0f, float speed = 1.0f) {
        if (!engine) {
            std::cerr << "Audio engine not initialized. Cannot load sound: " << soundName << std::endl;
            return;
        }

        std::cout << "Attempting to load sound: " << soundName << std::endl;
        auto it = sounds.find(soundName);
        if (it != sounds.end()) {
            engine->removeSoundSource(it->second);
        }

        ISoundSource* sound = engine->addSoundSourceFromFile(filePath.c_str());
        if (sound) {
            sounds[soundName] = sound;
            soundTypes[soundName] = type;
            soundVolumes[soundName] = volume;
            soundSpeeds[soundName] = speed;
            std::cout << "Sound loaded: " << soundName << std::endl;
        }
        else {
            std::cerr << "Failed to load sound: " << soundName << std::endl;
        }
    }

    void PlaySound(const std::string& soundName, bool loop = false) {
        if (!engine) {
            std::cerr << "Audio engine not initialized. Cannot play sound: " << soundName << std::endl;
            return;
        }

        if (IsSoundPaused(soundName)) {
            ResumeSound(soundName); // Resume the sound if it's paused
        }
        else {
            auto it = sounds.find(soundName);
            if (it != sounds.end()) {
                ISound* sound = engine->play2D(it->second, loop, true, true);
                if (sound) {
                    float volume = soundVolumes[soundName];
                    if (soundTypes[soundName] == SFX) {
                        volume *= sfxVolumeMultiplier;
                    }
                    else if (soundTypes[soundName] == Music) {
                        volume *= musicVolumeMultiplier;
                    }
                    sound->setVolume(volume);
                    sound->setPlaybackSpeed(soundSpeeds[soundName]);
                    sound->setIsPaused(false);
                    playingSounds[soundName].push_back(sound);
                }
                else {
                    std::cerr << "Failed to play sound: " << soundName << std::endl;
                }
            }
        }
    }

    void PauseSound(const std::string& soundName) {
        if (!engine) {
            std::cerr << "Audio engine not initialized. Cannot pause sound: " << soundName << std::endl;
            return;
        }

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
        if (!engine) {
            std::cerr << "Audio engine not initialized. Cannot resume sound: " << soundName << std::endl;
            return;
        }

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
        if (!engine) {
            std::cerr << "Audio engine not initialized. Cannot stop sound: " << soundName << std::endl;
            return;
        }

        auto it = playingSounds.find(soundName);
        if (it != playingSounds.end()) {
            for (auto& sound : it->second) {
                if (sound && !sound->isFinished()) {
                    sound->stop();
                    sound->drop(); // Properly release the sound
                }
            }
            it->second.clear(); // Clear the list of sounds
        }
    }

    bool IsSoundPaused(const std::string& soundName) {
        if (!engine) {
            std::cerr << "Audio engine not initialized. Cannot check if sound is paused: " << soundName << std::endl;
            return false;
        }

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
        if (!engine) {
            std::cerr << "Audio engine not initialized. Cannot set master volume." << std::endl;
            return;
        }

        // Set the master volume (0.0 to 1.0)
        engine->setSoundVolume(volume);
    }

    void SetPlaybackSpeed(const std::string& soundName, float speed) {
        if (!engine) {
            std::cerr << "Audio engine not initialized. Cannot set playback speed for sound: " << soundName << std::endl;
            return;
        }

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
        if (!engine) {
            std::cerr << "Audio engine not initialized. Cannot check if sound is finished: " << soundName << std::endl;
            return true;
        }

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
        if (!engine) {
            std::cerr << "Audio engine not initialized. Cannot set volume for sound: " << soundName << std::endl;
            return;
        }

        // Set the volume for a specific sound
        soundVolumes[soundName] = volume; // Update the volume in the map

        // Adjust the volume for all currently playing instances of this sound
        auto it = playingSounds.find(soundName);
        if (it != playingSounds.end()) {
            for (auto& sound : it->second) {
                if (sound && !sound->isFinished()) {
                    float adjustedVolume = volume;
                    if (soundTypes[soundName] == SFX) {
                        adjustedVolume *= sfxVolumeMultiplier;
                    }
                    else if (soundTypes[soundName] == Music) {
                        adjustedVolume *= musicVolumeMultiplier;
                    }
                    sound->setVolume(adjustedVolume);
                }
            }
        }
    }



    bool IsSoundPlaying(const std::string& soundName) {
        if (!engine) {
            std::cerr << "Audio engine not initialized. Cannot check if sound is playing: " << soundName << std::endl;
            return false;
        }

        auto it = playingSounds.find(soundName);
        if (it != playingSounds.end()) {
            for (auto& sound : it->second) {
                if (sound && !sound->isFinished() && !sound->getIsPaused()) {
                    return true; // Sound is currently playing
                }
            }
        }
        return false; // Sound is not playing
    }

    void SetSFXVolumeMultiplier(float multiplier) {
        sfxVolumeMultiplier = multiplier;
        ApplyVolumeMultiplier(SFX, multiplier);
    }

    void SetMusicVolumeMultiplier(float multiplier) {
        musicVolumeMultiplier = multiplier;
        ApplyVolumeMultiplier(Music, multiplier);
    }

private:
    AudioManager() {
        // Initialize the sound engine
        engine = createIrrKlangDevice();
        if (!engine) {
            std::cerr << "Could not create sound engine." << std::endl;
        }
    }

    void ApplyVolumeMultiplier(SoundType type, float multiplier) {
        for (auto& pair : playingSounds) {
            const std::string& soundName = pair.first;
            if (soundTypes[soundName] == type) {
                for (auto* sound : pair.second) {
                    if (sound && !sound->isFinished()) {
                        float adjustedVolume = soundVolumes[soundName] * multiplier;
                        sound->setVolume(adjustedVolume);
                    }
                }
            }
        }
    }

    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;
    ISoundEngine* engine = nullptr;
    std::unordered_map<std::string, ISoundSource*> sounds;
    std::unordered_map<std::string, std::vector<ISound*>> playingSounds;
    std::unordered_map<std::string, float> soundVolumes;
    std::unordered_map<std::string, float> soundSpeeds;
    std::unordered_map<std::string, SoundType> soundTypes;
    float sfxVolumeMultiplier = 1.0f;
    float musicVolumeMultiplier = 1.0f;
};
