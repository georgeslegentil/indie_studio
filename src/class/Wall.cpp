#include <random>
#include <stdexcept>
#include "class/Wall.hpp"

Wall::Wall(irr::IrrlichtDevice *device, bool unbreackable)
{
    this->_device = device;
    this->_unbreackable = unbreackable;
    if (this->_unbreackable)
        this->create3dModel("", "media/img/border_texture.png");
    else
        this->create3dModel("", "media/img/wall.png");
}

IEntity::type Wall::getType() const
{
    return IEntity::type::WALL;
}

void Wall::create3dModel(std::string modelFilePath, std::string textureFilePath)
{
    irr::video::IVideoDriver *driver = this->_device->getVideoDriver();
    irr::scene::ISceneManager *manager = this->_device->getSceneManager();

    irr::scene::IMeshSceneNode *node = manager->addCubeSceneNode(this->_scale);
    if (!node) {
        this->_device->drop();
        throw;
    }
    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    node->setMaterialTexture(0, driver->getTexture(textureFilePath.c_str()));
    this->_node = node;
}