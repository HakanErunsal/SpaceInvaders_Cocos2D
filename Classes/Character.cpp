#include "GameManager.h"
#include "Character.h"

USING_NS_CC;

void Character::Start()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(Character::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Character::onTouchEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, CharacterSprite);
	CharacterSprite->schedule(schedule_selector(Character::ShootTimer), 1.5f);
}

void Character::update(float delta)
{
	MoveCharacter(MovementSpeed);
}

void Character::SetCharacter(cocos2d::Size VisibleSize, cocos2d::Vec2 Origin)
{
	CharacterSprite = cocos2d::Sprite::create("Game/SpaceShip.png");
	CharacterSprite->setPosition(cocos2d::Vec2((VisibleSize.width / 2) + Origin.x, (VisibleSize.height / 8) + Origin.y));
	CharacterSprite->setScale(0.35f, 0.35f);
	

	auto SpriteBody = PhysicsBody::createCircle(CharacterSprite->getContentSize().width / 2, PhysicsMaterial(0, 1, 0));
	SpriteBody->setDynamic(false);
	SpriteBody->setCollisionBitmask(1);
	SpriteBody->setContactTestBitmask(true);
	CharacterSprite->setPhysicsBody(SpriteBody);

	Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);

	Start();
}

void Character::MoveCharacter(float Speed)
{
	CharacterSprite->setPosition(Vec2(CharacterSprite->getPosition().x + Speed, CharacterSprite->getPosition().y));
}

void Character::Shoot()
{
	if (this->isVisible())
	{
		Bullet* Bullet_ = GameManager::GetFromPool();
		if (Bullet_ != nullptr)
		{
			Bullet_->BulletSprite->setVisible(true);
			Bullet_->BulletSprite->setPosition(this->getPosition().x, this->getPosition().y + 35);
			Bullet_->LaunchBullet(false);
		}
	}
}

void Character::ShootTimer(float dt)
{
	Shoot();
}

bool Character::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event)
{
	if (touch->getLocation().x < Director::getInstance()->getVisibleSize().width / 2)
	{
		MovementSpeed = -3.f;
	}
	else
	{
		MovementSpeed = 3.f;
	}
	return true;
}

bool Character::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event)
{
	MovementSpeed = 0.f;
	return true;
}