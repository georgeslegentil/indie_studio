#include <stdexcept>
#include "class/Player.hpp"
#include "class/Bomb.hpp"

Player::Player(irr::IrrlichtDevice *device, const std::string &name)
{
    irr::video::IVideoDriver *driver = device->getVideoDriver();
    irr::scene::ISceneManager *smgr = device->getSceneManager();

    this->_device = device;
    this->_bombLimit = 3;
    this->create3dModel("media/player.md2", "media/sydney.bmp");
}

IEntity::type Player::getType() const
{
    return IEntity::type::PLAYER;
}

std::shared_ptr<Bomb> Player::plantBomb()
{
    if (this->_plantedBomb.size() > this->_bombLimit)
        throw;
    auto bomb = std::make_shared<Bomb>(*this, this->_device);
    bomb->setPosition(this->getPosition());
    this->_plantedBomb.push_back(bomb);
    return bomb;
}

int Player::getBombLimit() const
{
    return this->_bombLimit;
}

void Player::setBombLimit(int bombLimit)
{
    this->_bombLimit = bombLimit;
}

void Player::create3dModel(std::string modelFilePath, std::string textureFilePath)
{
    irr::video::IVideoDriver *driver = this->_device->getVideoDriver();
    irr::scene::ISceneManager *manager = this->_device->getSceneManager();
    irr::gui::IGUIEnvironment *gui = this->_device->getGUIEnvironment();
    irr::scene::IAnimatedMesh *mesh = manager->getMesh(modelFilePath.c_str());

    if (!mesh) {
        this->_device->drop();
        throw;
    }
    auto node = manager->addAnimatedMeshSceneNode(mesh);
    if (!node) {
        this->_device->drop();
        throw;
    }
    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    node->setMD2Animation(irr::scene::EMAT_STAND);
    node->setMaterialTexture(0, driver->getTexture(textureFilePath.c_str()));
    node->setScale(irr::core::vector3d<float>(0.25, 0.5, 0.25));
    this->_node = node;
}

void Player::setKeys(irr::EKEY_CODE up, irr::EKEY_CODE down, irr::EKEY_CODE left,
    irr::EKEY_CODE right, irr::EKEY_CODE plant)
{
    this->moveUpKey = up;
    this->moveDownKey = down;
    this->moveLeftKey = left;
    this->moveRightKey = right;
    this->plantBombKey = plant;
}

int Player::getBombRemaining() const
{
    return this->_bombLimit - this->_plantedBomb.size();
}

void Player::process()
{
    for (auto it = this->_plantedBomb.begin(); it != this->_plantedBomb.end();) {
        if ((*it)->hasExploded()) {
            this->_plantedBomb.erase(it);
            continue;
        }
        it++;
    }
}

void Player::setStandAnimation()
{
    if (!this->_node || this->_lastAnimationType == irr::scene::EMAT_STAND)
        return;
    static_cast<irr::scene::IAnimatedMeshSceneNode *>(this->_node)->setMD2Animation(
        irr::scene::EMAT_STAND);
    this->_lastAnimationType = irr::scene::EMAT_STAND;
}

void Player::setRunAnimation()
{
    if (!this->_node || this->_lastAnimationType == irr::scene::EMAT_RUN)
        return;
    static_cast<irr::scene::IAnimatedMeshSceneNode *>(this->_node)->setMD2Animation(
        irr::scene::EMAT_RUN);
    this->_lastAnimationType = irr::scene::EMAT_RUN;
}
