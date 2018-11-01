#pragma once

#include "cocos2d.h"
#include "Bullet.h"

class Enemy : public cocos2d::Node
{
public:
	void Start();

	void SetCharacter();

	void Shoot();
	void ShootTimer(float dt);

	cocos2d::Sprite* CharacterSprite;
};