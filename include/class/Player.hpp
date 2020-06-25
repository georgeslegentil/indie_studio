#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <memory>
#include <irrlicht/irrlicht.h>
#include "Entity.hpp"
#include "Map.hpp"

class Bomb;

class Player : public Entity 
{
    public:
        Player(irr::IrrlichtDevice *device, const std::string &name);
    public:
        type getType() const override;
        int getBombLimit() const;
        int getBombRemaining() const;

     //   void setScore(int score);
        void setBombLimit(int bombLimit);
        void setKeys(irr::EKEY_CODE up, irr::EKEY_CODE down, irr::EKEY_CODE left,
            irr::EKEY_CODE right, irr::EKEY_CODE plant);

        void process();
        std::shared_ptr<Bomb> plantBomb();
        void setStandAnimation();
        void setRunAnimation();
    protected:
        void create3dModel(std::string modelFilePath, std::string textureFilePath) override;
    public:
        irr::EKEY_CODE moveUpKey;
        irr::EKEY_CODE moveDownKey;
        irr::EKEY_CODE moveLeftKey;
        irr::EKEY_CODE moveRightKey;
        irr::EKEY_CODE plantBombKey;
    private:
       // int _score = 0;
        int _bombLimit;
        int _bombRange = 1;
        std::vector<std::shared_ptr<Bomb>> _plantedBomb;
        irr::scene::EMD2_ANIMATION_TYPE _lastAnimationType;
};

#endif
