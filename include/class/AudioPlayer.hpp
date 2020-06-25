#ifndef AUDIOPLAYER_HPP
#define AUDIOPLAYER_HPP

#include <vector>
#include <string>

class AudioPlayer {
public:
    enum songId {
        SONG_THEME,
        SONG_EXPLOSION,
        SONG_MEGUMIN
    };

    virtual void play(songId id) = 0;
    virtual void playLoop(songId id) = 0;
    virtual void pause(songId id) = 0;
    virtual void stop(songId id) = 0;
    virtual bool isPlaying(songId id) = 0;
    virtual void setSongVolume(songId id, int volume) = 0;
};

const std::vector<std::pair<AudioPlayer::songId, std::string>> SONG_PATH_LIST = {
    {AudioPlayer::SONG_THEME, "media/audio/theme.ogg"},
    {AudioPlayer::SONG_EXPLOSION, "media/audio/explosion.ogg"},
    {AudioPlayer::SONG_MEGUMIN, "media/audio/megumin_explosion.ogg"}
};

#endif
