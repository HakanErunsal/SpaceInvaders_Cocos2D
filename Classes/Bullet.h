#pragma once

#include "cocos2d.h"

class Bullet
{
public:
	Bullet();

	cocos2d::Sprite* BulletSprite;

	void LaunchBullet(bool ToTop);

	bool TargetUp;

	void ActionEnd();
};