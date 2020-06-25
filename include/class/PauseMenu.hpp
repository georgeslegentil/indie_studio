#ifndef PAUSEMENU_HPP
#define PAUSEMENU_HPP

#include <memory>
#include <irrlicht/irrlicht.h>

class PauseMenu {
public:
    PauseMenu(irr::IrrlichtDevice *device);

    void update();
    void startGame(size_t playerNumber);

    irr::IrrlichtDevice *getDevice() const;
private:
    irr::IrrlichtDevice *_device;
    bool _inPause;
    void createMenu();
    bool windowSizeHasChanged();

protected:
    // SFMLAudioPlayer _audioPlayer;
    bool _inGame = false;
};

#endif
