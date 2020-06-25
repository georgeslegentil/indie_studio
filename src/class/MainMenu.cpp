#include "class/MainMenu.hpp"
#include "class/MainMenuEvent.hpp"
#include "class/AudioPlayer.hpp"
#include "class/Game.hpp"

MainMenu::MainMenu(irr::IrrlichtDevice *device) : _device(device),
    _audioPlayer(SFMLAudioPlayer(SONG_PATH_LIST))
{
    this->_blockDensity = 2;
    this->_mapSize = 15;
    this->_YmapSize = 100;
    device->setEventReceiver(new MainMenuEvent(*this));
    this->createMenu();
}

irr::IrrlichtDevice *MainMenu::getDevice() const
{
    return this->_device;
}

void MainMenu::setBlockDensity(int density)
{
    this->_blockDensity = density;
}

void MainMenu::setMapSize(int mapSize)
{
    this->_mapSize = mapSize;
}

void MainMenu::setYMapSize(int Yvalue)
{
    this->_YmapSize = Yvalue;
}

void MainMenu::createMenu()
{
    irr::video::IVideoDriver *driver = this->_device->getVideoDriver();
    irr::gui::IGUIEnvironment *gui = this->_device->getGUIEnvironment();
    irr::gui::IGUISkin *skin = gui->getSkin();
    irr::gui::IGUIFont *font = gui->getFont("media/font/fontcourier.bmp");
    auto background = driver->getTexture("media/img/menu.png");
    int buttonWidth = 100;
    int buttonHeight = 30;
    int posXleft = driver->getScreenSize().Width / 4 - buttonWidth / 2;
    int posXright = (driver->getScreenSize().Width / 4) * 3 - buttonWidth / 2;
    int posY = driver->getScreenSize().Height / 2 - buttonHeight / 2;

    if (!font)
        throw;
    if (!background)
        throw;
    skin->setFont(font);
    gui->addImage(background, irr::core::vector2d<int>(0, 0), false, gui->getRootGUIElement());

// Button BASICS

    gui->addButton(irr::core::rect<irr::s32>(posXleft - 80, posY , posXleft - 80 + buttonWidth, posY + buttonHeight),
        nullptr, MainMenuEvent::GUI_ID_NEW_GAME, L"Start Game", L"Start a new game");
    gui->addButton(irr::core::rect<irr::s32>(posXleft - 80, posY + 230, posXleft - 80 + buttonWidth, posY + 230 + buttonHeight),
        nullptr, MainMenuEvent::GUI_ID_LOAD_GAME, L"Load Game", L"Load last saved game");
    gui->addButton(irr::core::rect<irr::s32>(posXright + 60, posY + 350, posXright + 60 + buttonWidth, posY + 350 + buttonHeight),
        nullptr, MainMenuEvent::GUI_ID_QUIT_BUTTON, L"Exit", L"Exit the game");

// Button GAMEMODE

    gui->addButton(irr::core::rect<irr::s32>(posXleft - 210, posY + 110, posXleft - 210 + buttonWidth, posY + 110 + buttonHeight),
        nullptr, MainMenuEvent::GUI_ID_EASY_GAME, L"Easy Game", L"Gamemode Easy");
    gui->addButton(irr::core::rect<irr::s32>(posXleft - 80, posY + 110, posXleft - 80 + buttonWidth, posY + 110 + buttonHeight),
        nullptr, MainMenuEvent::GUI_ID_NORMAL_GAME, L"Normal Game", L"Gamemode Normal");
    gui->addButton(irr::core::rect<irr::s32>(posXleft + 40, posY + 110, posXleft + 40 + buttonWidth, posY + 110 + buttonHeight),
        nullptr, MainMenuEvent::GUI_ID_HARD_GAME, L"Hard Game", L"Gamemode Hard");

// Button NBR OF PLAYERS

    gui->addButton(irr::core::rect<irr::s32>(posXright - 40, posY, posXright - 40 + buttonWidth, posY + buttonHeight),
        nullptr, MainMenuEvent::GUI_ID_2_PLAYERS, L"2 Players", L"Gamemode 2 Players");
    gui->addButton(irr::core::rect<irr::s32>(posXright + 80, posY, posXright + 80 + buttonWidth, posY + buttonHeight),
        nullptr, MainMenuEvent::GUI_ID_3_PLAYERS, L"3 Players", L"Gamemode 3 Players");
    gui->addButton(irr::core::rect<irr::s32>(posXright + 200, posY, posXright + 200 + buttonWidth, posY + buttonHeight),
        nullptr, MainMenuEvent::GUI_ID_4_PLAYERS, L"4 Players", L"Gamemode 4 Players");
    gui->addButton(irr::core::rect<irr::s32>(posXright + 80, posY + 130, posXright + 80 + buttonWidth, posY + 130 + buttonHeight),
        nullptr, MainMenuEvent::GUI_ID_GAME_INFO, L"Game Info", L"Game Info");

    this->_audioPlayer.playLoop(AudioPlayer::SONG_THEME);
}

void MainMenu::update()
{
    if (this->_inGame) {
        this->_game->gameLoop();
        return;
    }
}

void MainMenu::launchGame(size_t playerNumber)
{
    irr::gui::IGUIEnvironment *gui = this->_device->getGUIEnvironment();

    this->_game = new Game(this->_device, playerNumber, this->_mapSize, this->_YmapSize, this->_blockDensity);
    this->_inGame = true;
    gui->clear();
}
