#pragma once
#include "DynamicObject.h"
#include "CTime.h"
#include "ExplosionEffect.h"
class Shurikein :
	public DynamicObject
{
public:
	bool jumped = false;
	bool jumping = false;
	CTime countManifest = CTime(2500);	
	CTime timeRest = CTime(1000);
	CTime timeBeHit = CTime(100);
	bool inMech = false;
	bool toLeft = true;
	int mech = 0; // 1:goAround || 2:rollAndJump || 3:spinAndJump || 0:manifest
	CTime timeMech1 = CTime(4750); //goAround
	CTime timeMech2 = CTime(4900); //rollAndJump
	CTime timeMech3 = CTime(1630 * 3); //spinAndJump
	bool hit = false;
	ExplosionEffect* effectExplosion = ExplosionEffect::getInstance();
	Shurikein();
	~Shurikein();
	Shurikein(UINT idTexture, float x = 0, float y = 0, float vx = 0, float vy = 0);
	void loadResources() override;
	Shurikein* clone(int id, int x, int y);
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects = 0, unordered_map<int, GameObject*>* dynamicObjects = 0) override;
	void collisionStatic(unordered_map<int, GameObject*>* staticObjects);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) override;
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
	void receiveDamage(int damage) override;
	void createExplosion(float x, float y) override;
};

