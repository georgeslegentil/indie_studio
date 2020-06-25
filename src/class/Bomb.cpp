#include <stdexcept>
#include "class/Bomb.hpp"
#include "class/Explosion.hpp"

Bomb::Bomb(Player &owner, irr::IrrlichtDevice *device) : _owner(owner)
{
    this->_device = device;
    this->create3dModel("media/bomb.md2", "");
}

Player &Bomb::getOwner() const
{
    return this->_owner;
}

int Bomb::getCountdown() const
{
    return this->_countdown;
}

int Bomb::getRange() const
{
    return this->_range;
}

const std::chrono::time_point<std::chrono::system_clock> &Bomb::getCreationTime() const
{
    return this->_creationTime;
}

bool Bomb::hasExploded()
{
    auto now = std::chrono::system_clock::now();
    int elapsedSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(
        now - this->_creationTime).count();
    return elapsedSeconds >= this->_countdown;
}

std::vector<std::shared_ptr<Explosion>> Bomb::createExplosion()
{
    std::vector<std::shared_ptr<Explosion>> list;
    float startX = this->getX() - this->_range;
    float startZ = this->getZ() - this->_range;
    int x = 0;
    int z = 0;

    while (x <= 2) {
        if (startX + x != this->getX())
            list.push_back(std::make_shared<Explosion>(*this, startX + x, this->getZ()));
        while (z <= 2) {
            if (startZ + z != this->getZ())
                list.push_back(std::make_shared<Explosion>(*this, this->getX(), startZ + z));
            z++;
        }
        x++;
    }
    list.push_back(std::make_shared<Explosion>(*this, this->getX(), this->getZ()));
    return list;
}

IEntity::type Bomb::getType() const
{
    return IEntity::type::BOMB;
}

void Bomb::create3dModel(std::string modelFilePath, std::string textureFilePath)
{
    irr::video::IVideoDriver *driver = this->_device->getVideoDriver();
    irr::scene::ISceneManager *manager = this->_device->getSceneManager();
    irr::gui::IGUIEnvironment *gui = this->_device->getGUIEnvironment();
    irr::scene::IMesh *mesh = manager->getMesh(modelFilePath.c_str());

    if (!mesh) {
        this->_device->drop();
        throw;
    }
    auto node = manager->addMeshSceneNode(mesh);
    if (!node) {
        this->_device->drop();
        throw;
    }
    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    node->setMaterialTexture(0, driver->getTexture(textureFilePath.c_str()));
    node->setScale({0.01, 0.01, 0.01});
    node->setRotation({-90, 0, 0});
    this->_node = node;
}