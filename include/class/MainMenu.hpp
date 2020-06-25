#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <memory>
#include <irrlicht/irrlicht.h>
#include "SFMLAudioPlayer.hpp"

class Game;

class MainMenu {
public:
    explicit MainMenu(irr::IrrlichtDevice *device);

    void update();
    void launchGame(size_t playerNumber);
    void setMapSize(int mapSize);
    void setYMapSize(int Yvalue);
    void setBlockDensity(int density);

    irr::IrrlichtDevice *getDevice() const;
private:
    void createMenu();

protected:
    irr::IrrlichtDevice *_device;
    SFMLAudioPlayer _audioPlayer;
    Game *_game;
    bool _inGame = false;
    int _playerNumber;
    int _blockDensity;
    int _mapSize;
    int _YmapSize;
};

#endif
