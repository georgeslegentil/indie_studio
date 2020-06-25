#include "class/Case.hpp"
#include "class/Map.hpp"

Case::Case(Map &parentMap, int x, int z) : _map(parentMap), _x(x), _z(z)
{}

const std::vector<std::shared_ptr<Entity>> &Case::getEntities() const
{
    return this->_entities;
}

void Case::pushEntity(const std::shared_ptr<Entity> &entity)
{
    entity->setPosition(this->_x, 0, this->_z);
    this->_entities.push_back(std::shared_ptr<Entity>(entity));
}

void Case::reset()
{
    for (auto &e : this->_entities)
        e->destroy();
    this->_entities.clear();
}

int Case::getX() const
{
    return this->_x;
}

int Case::getZ() const
{
    return this->_z;
}

bool Case::hasWall()
{
    for (auto &e : this->_entities) {
        if (e->getType() == IEntity::type::WALL)
            return true;
    }
    return false;
}

void Case::deleteFromMap()
{
    auto i = this->_entities.begin();
    
    while(i != this->_entities.end()) {
        if ((*i)->mustBeDestroyed()) {
            this->_entities.erase(i);
            continue;
        }
        i++;
    }
}

void Case::removeWalls()
{
    for (auto &entity : this->_entities)
        if (entity->getType() == IEntity::type::WALL && !entity->isUnbreackable())
            entity->destroy();
}