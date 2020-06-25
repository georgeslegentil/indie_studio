#ifndef SFMLAUDIOPLAYER_HPP
#define SFMLAUDIOPLAYER_HPP

#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio/SoundSource.hpp>
#include <map>
#include "AudioPlayer.hpp"

class SFMLAudioPlayer : AudioPlayer {
public:
    explicit SFMLAudioPlayer(
        const std::vector<std::pair<AudioPlayer::songId, std::string>> &songPathList);
    void play(songId id) override;
    void playLoop(songId id) override;
    void pause(songId id) override;
public:
    void stop(songId id) override;
    bool isPlaying(songId id) override;
    void setSongVolume(songId id, int volume) override;

private:
    std::map<songId, sf::Music *> _music;
};

#endif
