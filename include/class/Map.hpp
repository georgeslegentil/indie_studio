#ifndef MAP_HPP
#define MAP_HPP

#include <cstdio>
#include "Case.hpp"

class Map {
public:
    Map(irr::IrrlichtDevice *device, size_t width, size_t length, size_t density);

public:
    void process();
    void pushEntity(const std::shared_ptr<Entity> &entity);
    void resetCase(int x, int y);

    Case &getCase(int x, int y);
    std::vector<Case> &getCases();
    size_t getWidth() const;
    size_t getHeight() const;
    bool isBorder(int x, int z);

private:
    void generateBorders();
    void generateWalls();
    void generateInvincibleWalls();
    void deleteFromMap();

private:
    irr::IrrlichtDevice *_device;
    size_t _width;
    size_t _height;
    size_t _blockDensity;
    std::vector<Case> _cases;
};

#endif
