#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <irrlicht/irrlicht.h>
#include "IEntity.hpp"

class Entity : public IEntity {
public:
    void destroy();
protected:
    void create3dModel(std::string modelFilePath, std::string textureFilePath) override;
public:
    void setPosition(float x, float y, float z) override;
    void setPosition(const irr::core::vector3df& position);
    irr::scene::IMesh *getMesh();
    type getType() const override;
    bool mustBeDestroyed() const override;
    float getX() const override;
    float getZ() const override;
    irr::core::vector3df getPosition();
    bool isUnbreackable() const override;
    irr::scene::ISceneNode *getNode() const;
    irr::IrrlichtDevice *getDevice() const;
protected:
    bool _mustBeDestroyed = false;
    bool _unbreackable = false;
    bool _movable = true;
    irr::IrrlichtDevice *_device;
    irr::scene::ISceneNode *_node;
    float _scale = 10;
};

#endif
