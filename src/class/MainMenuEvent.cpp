#include "class/MainMenuEvent.hpp"

MainMenuEvent::MainMenuEvent(MainMenu &menu) : _mainMenu(menu)
{}

bool MainMenuEvent::OnEvent(const irr::SEvent &event)
{
    auto device = this->_mainMenu.getDevice();
    irr::video::IVideoDriver *driver = this->_mainMenu.getDevice()->getVideoDriver();
    irr::gui::IGUIEnvironment *gui = this->_mainMenu.getDevice()->getGUIEnvironment();

    if (event.EventType == irr::EET_GUI_EVENT) {
        irr::s32 id = event.GUIEvent.Caller->getID();
        if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
            switch (id) {
                case GUI_ID_QUIT_BUTTON:
                    device->closeDevice();
                    return true;
                case GUI_ID_NEW_GAME:
                    this->_mainMenu.launchGame(1);
                    return true;
                case GUI_ID_EASY_GAME:
                    this->_mainMenu.setBlockDensity(2);
                    this->_mainMenu.setMapSize(15);
                    this->_mainMenu.setYMapSize(100);
                    return true;
                case GUI_ID_NORMAL_GAME:
                    this->_mainMenu.setBlockDensity(2);
                    this->_mainMenu.setMapSize(19);
                    this->_mainMenu.setYMapSize(130);
                    return true;
                case GUI_ID_HARD_GAME:
                    this->_mainMenu.setBlockDensity(2);
                    this->_mainMenu.setMapSize(23);
                    this->_mainMenu.setYMapSize(170);
                    return true;
                case GUI_ID_LOAD_GAME:
                    return true;
                case GUI_ID_2_PLAYERS:
                    this->_mainMenu.launchGame(2);
                    return true;
                case GUI_ID_3_PLAYERS:
                    this->_mainMenu.launchGame(3);
                    return true;
                case GUI_ID_4_PLAYERS:
                    this->_mainMenu.launchGame(4);
                    return true;
                case GUI_ID_GAME_INFO:
                    auto image = driver->getTexture("media/img/rules.png");
                    gui->addImage(image, irr::core::vector2d<int>(0, 0), false, gui->getRootGUIElement());
                    return true;
            }
        }
    }
    return false;
}