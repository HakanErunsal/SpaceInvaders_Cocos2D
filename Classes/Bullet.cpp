#include "Bullet.h"

USING_NS_CC;

Bullet::Bullet()
{
	BulletSprite = cocos2d::Sprite::create("Game/Bullet.png");
	BulletSprite->setScale(1.f, 1.f);

	auto SpriteBody = PhysicsBody::createCircle(BulletSprite->getContentSize().width / 2, PhysicsMaterial(0, 1, 0));
	SpriteBody->setDynamic(false);
	SpriteBody->setCollisionBitmask(0);
	SpriteBody->setContactTestBitmask(true);
	BulletSprite->setPhysicsBody(SpriteBody);
}

void Bullet::LaunchBullet(bool ToTop)
{
	BulletSprite->stopAllActions();

	TargetUp = ToTop;
	if (TargetUp == true)
	{
		auto move = MoveTo::create(3.0, Vec2(BulletSprite->getPosition().x, 0));
		BulletSprite->runAction(Sequence::create(move, CallFunc::create(CC_CALLBACK_0(Bullet::ActionEnd, this)), NULL));
	}
	else
	{
		auto move = MoveTo::create(3.0, Vec2(BulletSprite->getPosition().x, Director::getInstance()->getVisibleSize().height));
		BulletSprite->runAction(Sequence::create(move, CallFunc::create(CC_CALLBACK_0(Bullet::ActionEnd, this)), NULL));
	}
}

void Bullet::ActionEnd()
{
	BulletSprite->setVisible(false);
}