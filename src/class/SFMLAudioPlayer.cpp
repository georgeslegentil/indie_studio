#include <class/SFMLAudioPlayer.hpp>

SFMLAudioPlayer::SFMLAudioPlayer(
    const std::vector<std::pair<AudioPlayer::songId, std::string>> &songPathList)
{
    for (auto &song : songPathList) {
        auto *songCreate = new sf::Music();
        if (!songCreate->openFromFile(song.second))
            throw;
        this->_music.insert(std::pair<AudioPlayer::songId, sf::Music *>(song.first, songCreate));
    }
}

void SFMLAudioPlayer::play(AudioPlayer::songId id)
{
    this->_music[id]->play();
}

void SFMLAudioPlayer::playLoop(AudioPlayer::songId id)
{
    this->play(id);
    this->_music.find(id)->second->setLoop(true);
}

void SFMLAudioPlayer::pause(AudioPlayer::songId id)
{
    this->_music.find(id)->second->pause();
}

void SFMLAudioPlayer::stop(AudioPlayer::songId id)
{
    this->_music.find(id)->second->stop();
}

bool SFMLAudioPlayer::isPlaying(AudioPlayer::songId id)
{
    return this->_music.find(id)->second->getStatus() == sf::SoundSource::Status::Playing;
}

void SFMLAudioPlayer::setSongVolume(AudioPlayer::songId id, int volume)
{
    if (volume >= 0 && volume <= 100)
        this->_music.find(id)->second->setVolume(static_cast<float>(volume));
}
