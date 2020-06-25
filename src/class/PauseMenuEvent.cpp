#include "class/PauseMenuEvent.hpp"

PauseMenuEvent::PauseMenuEvent(PauseMenu &menu) : _pauseMenu(menu)
{
}

bool PauseMenuEvent::OnEvent(const irr::SEvent &event)
{
    auto device = this->_pauseMenu.getDevice();

    if (event.EventType == irr::EET_GUI_EVENT) {
        irr::s32 id = event.GUIEvent.Caller->getID();
        switch (event.GUIEvent.EventType) {
            case irr::gui::EGET_BUTTON_CLICKED:
                switch (id) {
                    case GUI_ID_QUIT_BUTTON:
                        device->closeDevice();
                        return true;
                }
        }
    }
    return false;
}
