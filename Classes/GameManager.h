#include "cocos2d.h"
#include "Character.h"
#include "Enemy.h"
#include "Bullet.h"

class GameManager : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void CreateCharacter();
	void CreateEnemies();
	Character* CurrentCharacter;

	void InitializePool(int PoolSize);
	static Bullet* AddToPool(Bullet* Bullet_);
	static Bullet* GetFromPool();
	static std::list<Bullet*> BulletList;

	bool onContactBegin(cocos2d::PhysicsContact &contact);

	int PoolSize = 20;

	CREATE_FUNC(GameManager);

private:
	cocos2d::Size VisibleSize;
	cocos2d::Vec2 Origin;

	cocos2d::PhysicsWorld* SceneWorld;
	void SetPhysicsWorld(cocos2d::PhysicsWorld* World) { SceneWorld = World; };
};