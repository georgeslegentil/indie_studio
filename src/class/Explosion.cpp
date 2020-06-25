#include "class/Explosion.hpp"
#include "class/Bomb.hpp"

Explosion::Explosion(Bomb &bomb, float x, float z) : _bomb(bomb)
{
    this->_device = bomb.getDevice();
    this->create3dModel("media/bomb.md2", "");
    this->setPosition(x, 0, z);
}

IEntity::type Explosion::getType() const
{
    return IEntity::type::EXPLOSION;
}

void Explosion::create3dModel(std::string modelFilePath, std::string textureFilePath)
{
    irr::scene::ISceneManager *manager = this->_device->getSceneManager();
    irr::video::IVideoDriver *driver = this->_device->getVideoDriver();
    irr::scene::ISceneNode *node = manager->addCubeSceneNode(this->_scale);

    if (!node) {
        this->_device->drop();
        throw;
    }
    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    node->setScale({1, 0.001, 1});
    node->setRotation({0, 0, 0});
    node->setMaterialTexture(0, driver->getTexture("media/img/explosion.png"));
    node->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
    this->_node = node;
}

bool Explosion::end()
{
    auto now = std::chrono::system_clock::now();
    int elapsedSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(
        now - this->_creationTime).count();
    return elapsedSeconds >= this->_duration;
}