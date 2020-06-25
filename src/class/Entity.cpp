#include <stdexcept>
#include "class/Entity.hpp"

float Entity::getX() const
{
    if (this->_node)
        return this->_node->getPosition().X / this->_scale;
    else
        throw;
}

float Entity::getZ() const
{
    if (this->_node)
        return this->_node->getPosition().Z / this->_scale;
    else
        throw;
}

bool Entity::isUnbreackable() const
{
    return this->_unbreackable;
}

IEntity::type Entity::getType() const
{
    return IEntity::type::NONE;
}

void Entity::setPosition(float x, float y, float z)
{
    if (this->_node)
        this->_node->setPosition(
            irr::core::vector3df(x * this->_scale, y * this->_scale, z * this->_scale));
    else
        throw;
}

bool Entity::mustBeDestroyed() const
{
    return this->_mustBeDestroyed;
}

void Entity::create3dModel(std::string modelFilePath, std::string textureFilePath)
{
}

void Entity::destroy()
{
    this->_node->remove();
    this->_mustBeDestroyed = true;
}

irr::scene::ISceneNode *Entity::getNode() const
{
    return this->_node;
}

irr::core::vector3df Entity::getPosition()
{
    if (this->_node)
        return this->getNode()->getPosition() / this->_scale;
    else
        throw;
}

void Entity::setPosition(const irr::core::vector3df &position)
{
    if (this->_node)
        this->_node->setPosition(position * this->_scale);
    else
        throw;
}

irr::scene::IMesh *Entity::getMesh()
{
    if (this->_node->getType() == irr::scene::ESNT_CUBE) {
        irr::scene::IMesh *mesh = static_cast<irr::scene::IMeshSceneNode *>(this->_node)->getMesh();
        return mesh;
    }
    return nullptr;
}

irr::IrrlichtDevice *Entity::getDevice() const
{
    return this->_device;
}
