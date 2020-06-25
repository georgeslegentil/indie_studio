#include <random>
#include "class/Map.hpp"
#include "class/Wall.hpp"

Map::Map(irr::IrrlichtDevice *device, size_t width, size_t length, size_t density) : _device(device), _width(width),
    _height(length), _blockDensity(density)
{
    for (int i = 0; i < this->_width * this->_height; ++i) {
        int x = i % this->_height;
        int y = i / this->_height;
        this->_cases.emplace_back(*this, x, y);
    }
    this->generateWalls();
    this->generateInvincibleWalls();
    this->generateBorders();
}

Case &Map::getCase(int x, int y)
{
    return this->_cases.at(this->_width * y + x);
}

void Map::resetCase(int x, int y)
{
    this->getCase(x, y).reset();
}

void Map::process()
{
    this->deleteFromMap();
}

void Map::deleteFromMap()
{
    for (auto &c : this->_cases)
        c.deleteFromMap();
}

size_t Map::getWidth() const
{
    return this->_width;
}

size_t Map::getHeight() const
{
    return this->_height;
}

void Map::pushEntity(const std::shared_ptr<Entity> &entity)
{
    this->getCase(static_cast<int>(round(entity->getX())),
        static_cast<int>(round(entity->getZ()))).pushEntity(entity);
}

void Map::generateWalls()
{
    for (int i = 1; i < this->_height-1; i++)
        for (int j = 1; j < this->_width-1; j++) {
            if ((std::rand() % 100)%this->_blockDensity <= 0)
                if (isBorder(j, i) && isBorder(i, j+1) && isBorder(i+1, j)
                 && isBorder(i-1, j) && isBorder(i, j-1))
                    this->getCase(i, j).pushEntity(std::make_shared<Wall>(this->_device, false));
        }
}

void Map::generateBorders()
{
    for (int j = 0; j < this->_width; ++j) {
        this->getCase(j, 0).pushEntity(std::make_shared<Wall>(this->_device, true));
        this->getCase(j, this->_height - 1).pushEntity(std::make_shared<Wall>(this->_device, true));
    }
    for (int j = 0; j < this->_height; ++j) {
        this->getCase(0, j).pushEntity(std::make_shared<Wall>(this->_device, true));
        this->getCase(this->_width - 1, j).pushEntity(std::make_shared<Wall>(this->_device, true));
    }
}

void Map::generateInvincibleWalls()
{
    for (int i = 2; i < this->_height-2; i+=2)
        for (int j = 2; j < this->_width-2; j+=2)
            this->getCase(i, j).pushEntity(std::make_shared<Wall>(this->_device, true));
}

bool Map::isBorder(int x, int z)
{
    if (x == this->_width - 2 && z == this->_height - 2 || 
        x == this->_width - 2 && z == 1 ||
        x == 1 && z == this->_height - 2 ||
        x == 1 && z == 1)
        return false;
    return true;
}

std::vector<Case> &Map::getCases()
{
    return this->_cases;
}
