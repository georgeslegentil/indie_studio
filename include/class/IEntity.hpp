#ifndef IENTITY_HPP
#define IENTITY_HPP

#include <string>

class IEntity {
public:
    enum type {
        NONE = 0, PLAYER, WALL, BOMB, EXPLOSION
    };
protected:
    virtual void create3dModel(std::string modelFilePath, std::string textureFilePath) = 0;
public:
    virtual void setPosition(float x, float y, float z) = 0;
public:
    virtual type getType() const = 0;
    virtual bool mustBeDestroyed() const = 0;
    virtual float getX() const = 0;
    virtual float getZ() const = 0;
    virtual bool isUnbreackable() const = 0;
};

#endif
