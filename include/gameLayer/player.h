#pragma once
#include <gl2d/gl2d.h>
#include <spaceShip.h>
#include <singleton.h>

class Player:public  SpaceShip
{
private:
	Player();
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
public:
	static Player& GetInstance();
	void Update(float deltaTime) override;
};