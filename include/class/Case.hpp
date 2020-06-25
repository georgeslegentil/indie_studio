#ifndef CASE_HPP
#define CASE_HPP

#include <vector>
#include <memory>
#include "MainMenu.hpp"
#include "Entity.hpp"

class Map;

class Case {
public:
    Case(Map &parentMap, int x, int z);
public:
    void pushEntity(const std::shared_ptr<Entity>& entity);
    void removeWalls();
    void reset();
    void deleteFromMap();
public:
    bool hasWall();
    const std::vector<std::shared_ptr<Entity>> &getEntities() const;
    int getX() const;
    int getZ() const;
private:
    Map &_map;
    int _x;
    int _z;
    std::vector<std::shared_ptr<Entity>> _entities;
};

#endif
