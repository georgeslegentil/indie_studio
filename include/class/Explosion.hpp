#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include <chrono>
#include "Entity.hpp"

class Bomb;

class Explosion : public Entity {
public:
    explicit Explosion(Bomb &bomb, float x = 0, float z = 0);
protected:
    void create3dModel(std::string modelFilePath, std::string textureFilePath) override;
public:
    type getType() const override;
    bool end();
private:
    Bomb &_bomb;
    int _damage = 1;
    int _duration = 100;
    std::chrono::time_point<std::chrono::system_clock> _creationTime = std::chrono::system_clock::now();
};

#endif
