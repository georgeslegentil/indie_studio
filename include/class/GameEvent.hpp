#ifndef GAMEEVENT_HPP
#define GAMEEVENT_HPP

#include <irrlicht/irrlicht.h>
#include "class/Game.hpp"

class GameEvent : public irr::IEventReceiver {
public:
    explicit GameEvent(Game &game);

    bool OnEvent(const irr::SEvent &event) override;

    bool pressedKey(irr::EKEY_CODE keyCode) const;

private:
    Game &_game;
    bool _pressedKey[irr::KEY_KEY_CODES_COUNT] = {false};
};

#endif
