#pragma once
#include <irrKlang/irrKlang.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

using namespace irrklang;

class AudioManager {
public:
    AudioManager() {
        // Initialize the sound engine
        engine = createIrrKlangDevice();
        if (!engine) throw std::runtime_error("Could not create sound engine.");
    }

    ~AudioManager() {
        // Clean up the sound engine
        for (auto& soundPair : playingSounds) {
            for (auto* sound : soundPair.second) {
                if (sound) {
                    sound->stop();
                    sound->drop(); // Release the sound
                }
            }
        }
        engine->drop();
    }

    void LoadSound(const std::string& soundName, const std::string& filePath, float volume = 1.0f) {
        // Load the sound into memory (preloading)
        ISoundSource* sound = engine->addSoundSourceFromFile(filePath.c_str());
        sounds[soundName] = sound;
        soundVolumes[soundName] = volume; // Store the default volume for this sound
    }

    void PlaySound(const std::string& soundName, bool loop = false) {
        // Play the sound with the given name
        auto it = sounds.find(soundName);
        if (it != sounds.end()) {
            ISound* sound = engine->play2D(it->second, loop, false, true);
            if (sound) {
                sound->setVolume(soundVolumes[soundName]); // Set the volume for this sound instance
                sound->setIsPaused(false);
                playingSounds[soundName].push_back(sound);
            }
        }
    }

    void StopSound(const std::string& soundName) {
        // Stop all instances of the sound with the given name
        auto it = playingSounds.find(soundName);
        if (it != playingSounds.end()) {
            for (auto& sound : it->second) {
                if (sound && !sound->isFinished()) {
                    sound->stop();
                    sound->drop(); // Release the sound
                }
            }
            it->second.clear(); // Remove all instances from the list
        }
    }

    void SetMasterVolume(float volume) {
        // Set the master volume (0.0 to 1.0)
        engine->setSoundVolume(volume);
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

private:
    ISoundEngine* engine;
    std::unordered_map<std::string, ISoundSource*> sounds;
    std::unordered_map<std::string, std::vector<ISound*>> playingSounds; // Tracks playing sounds
    std::unordered_map<std::string, float> soundVolumes; // New map for individual sound volumes
};
