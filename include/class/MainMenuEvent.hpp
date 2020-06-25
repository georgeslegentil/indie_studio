#ifndef MAINMENUEVENT_HPP
#define MAINMENUEVENT_HPP

#include <irrlicht/irrlicht.h>
#include "MainMenu.hpp"

class MainMenuEvent : public irr::IEventReceiver {
public:
    enum {
        GUI_ID_QUIT_BUTTON = 101, GUI_ID_NEW_GAME, GUI_ID_LOAD_GAME, GUI_ID_EASY_GAME,  GUI_ID_NORMAL_GAME,  GUI_ID_HARD_GAME,
        GUI_ID_2_PLAYERS, GUI_ID_3_PLAYERS, GUI_ID_4_PLAYERS, GUI_ID_GAME_INFO, GUI_ID_QUIT_INFO
    };

    explicit MainMenuEvent(MainMenu &menu);

    bool OnEvent(const irr::SEvent &event) override;
private:
    MainMenu &_mainMenu;
};

#endif
