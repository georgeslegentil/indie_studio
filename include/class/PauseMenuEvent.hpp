#ifndef PAUSEMENUEVENT_HPP
#define PAUSEMENUEVENT_HPP

#include <irrlicht/irrlicht.h>
#include "iostream"
#include "PauseMenu.hpp"

class PauseMenuEvent : public irr::IEventReceiver 
{
public:
    enum {
        GUI_ID_QUIT_BUTTON = 101
    };
    explicit PauseMenuEvent(PauseMenu &menu);
    bool getStatus() const;
    void setStatus(bool status);

    bool OnEvent(const irr::SEvent &event) override;
private:
    bool _inPause;
    PauseMenu _pauseMenu;
};

#endif