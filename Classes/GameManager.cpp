#include "GameManager.h"

USING_NS_CC;

std::list<Bullet*> GameManager::BulletList;

cocos2d::Scene * GameManager::createScene()
{
	auto Scene = Scene::createWithPhysics();

	auto Layer = GameManager::create();
	Layer->SetPhysicsWorld(Scene->getPhysicsWorld());

	Scene->addChild(Layer);

	return Scene;
}

bool GameManager::init()
{
	if (!Layer::init())
	{
		return false;
	}

	VisibleSize = Director::getInstance()->getVisibleSize();
	Origin = Director::getInstance()->getVisibleOrigin();

	CreateCharacter();
	CreateEnemies();

	InitializePool(PoolSize);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameManager::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}

//Spawn Characters
void GameManager::CreateCharacter()
{
	CurrentCharacter = new Character();
	CurrentCharacter->SetCharacter(VisibleSize, Origin);
	this->addChild(CurrentCharacter->CharacterSprite);
}

void GameManager::CreateEnemies()
{
	for (int i = 1; i < 7; i++)
	{
		Enemy* Enemy_ = new Enemy();
		Enemy_->SetCharacter();
		Enemy_->CharacterSprite->setPosition(VisibleSize.width / 7 * i, VisibleSize.height / 1.2f);
		this->addChild(Enemy_->CharacterSprite);
	}
}

//Bullet Pool
void GameManager::InitializePool(int PoolSize)
{
	for (int i = 0; i < PoolSize; i++)
	{
		Bullet* Bullet_ = new Bullet();
		this->addChild(Bullet_->BulletSprite);
		AddToPool(Bullet_);
	}
}

Bullet * GameManager::AddToPool(Bullet* Bullet_)
{
	Bullet_->BulletSprite->setVisible(false);
	Bullet_->BulletSprite->setPosition(0, 0);
	BulletList.push_back(Bullet_);
	return Bullet_;
}

Bullet * GameManager::GetFromPool()
{
	for each (Bullet* Bullet_ in BulletList)
	{
		if (Bullet_ != nullptr && Bullet_->BulletSprite->isVisible() == false)
		{
			return Bullet_;
		}
	}
}

//Collisions
bool GameManager::onContactBegin(cocos2d::PhysicsContact & contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	if ((0 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()) || (1 == a->getCollisionBitmask() && 0 == b->getCollisionBitmask()))
	{
		CCLOG("Bullet hit");
		a->getNode()->setVisible(false);
		b->getNode()->setVisible(false);
	}
	if ((0 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()) || (2 == a->getCollisionBitmask() && 0 == b->getCollisionBitmask()))
	{
		CCLOG("Bullet hit");
		a->getNode()->setVisible(false);
		b->getNode()->setVisible(false);
	}
	return true;
}