#include "class/GameEvent.hpp"

GameEvent::GameEvent(Game &game) : _game(game)
{}

bool GameEvent::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
            this->_pressedKey[event.KeyInput.Key] = event.KeyInput.PressedDown;
        if (event.KeyInput.PressedDown) {
            this->_game.eventKey(event.KeyInput.Key);
        }
    }
    return false;
}

bool GameEvent::pressedKey(irr::EKEY_CODE keyCode) const
{
    return this->_pressedKey[keyCode];
}
