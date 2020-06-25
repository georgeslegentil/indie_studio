#include <stdexcept>
#include <memory>
#include <irrlicht/irrlicht.h>
#include "class/MainMenu.hpp"
#include "class/Player.hpp"

static irr::IrrlichtDevice *createWindow()
{
    irr::IrrlichtDevice *device = irr::createDevice(irr::video::EDT_OPENGL,
        irr::core::dimension2d<irr::u32>(1400, 900), 16, false, false, false, nullptr);

    if (!device)
        throw;
    device->setWindowCaption(L"Indie Studio");
    device->setResizable(false);

    return device;
}

static void loop(irr::IrrlichtDevice *device, MainMenu &menu)
{
    irr::video::IVideoDriver *driver = device->getVideoDriver();
    irr::scene::ISceneManager *manager = device->getSceneManager();
    irr::gui::IGUIEnvironment *gui = device->getGUIEnvironment();

    while (device->run() && driver) {
        if (device->isWindowActive()) {
            driver->beginScene(true, true, irr::video::SColor(0, 153, 208, 242));
            menu.update();
            manager->drawAll();
            gui->drawAll();
            driver->endScene();
        }
    }
    device->drop();
}

int main()
{
    auto device = createWindow();

    auto mainMenu = MainMenu(device);
    loop(device, mainMenu);
    return 0;
}