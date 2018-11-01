#include "GameManager.h"
#include "Enemy.h"

USING_NS_CC;

void Enemy::Start()
{
	int Delay = cocos2d::RandomHelper::random_int(2, 10);
	CharacterSprite->schedule(schedule_selector(Enemy::ShootTimer), Delay);
}

void Enemy::SetCharacter()
{
	CharacterSprite = cocos2d::Sprite::create("Game/Fighter.png");
	CharacterSprite->setScale(0.35f, -0.35f);

	auto SpriteBody = PhysicsBody::createCircle(CharacterSprite->getContentSize().width / 6, PhysicsMaterial(0, 1, 0));
	SpriteBody->setDynamic(false);
	SpriteBody->setCollisionBitmask(2);
	SpriteBody->setContactTestBitmask(true);
	CharacterSprite->setPhysicsBody(SpriteBody);

	Start();
}

void Enemy::Shoot()
{
	if (this->isVisible())
	{
		Bullet* Bullet_ = GameManager::GetFromPool();
		if (Bullet_ != nullptr)
		{
			Bullet_->BulletSprite->setVisible(true);
			Bullet_->BulletSprite->setPosition(this->getPosition().x, this->getPosition().y - 35);
			Bullet_->LaunchBullet(true);
		}
	}
}

void Enemy::ShootTimer(float dt)
{
	Shoot();
}
