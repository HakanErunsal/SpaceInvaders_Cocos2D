#pragma once

#include "cocos2d.h"
#include "Bullet.h"

class Character : public cocos2d::Node
{
public:
	void Start();

	void update(float);

	void SetCharacter(cocos2d::Size VisibleSize, cocos2d::Vec2 Origin);

	void MoveCharacter(float Speed);

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
	bool onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event);

	void Shoot();
	void ShootTimer(float dt);

	float MovementSpeed;

	cocos2d::Sprite* CharacterSprite;

};