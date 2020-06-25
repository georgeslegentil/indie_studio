#ifndef WALL_HPP
#define WALL_HPP

#include "Entity.hpp"

class Item;

class Wall : public Entity {
public:
    Wall(irr::IrrlichtDevice *device, bool invincible);
protected:
    void create3dModel(std::string modelFilePath, std::string textureFilePath) override;
public:
    type getType() const override;
    //Item *destroy();
};

#endif
