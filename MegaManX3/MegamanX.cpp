#include "MegamanX.h"
#include "Brick.h"



void MegamanX::collisionStatic(unordered_map<int, CTreeObject*>* staticObjects)
{
	vector<CollisionEvent*> coEvents;
	vector<CollisionEvent*> coEventsResult;

	collision->findCollisions(dt, this, *staticObjects, coEvents);
	//debugOut(L" %d\n", coEvents.size());
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		//onAir = true;
		//if(onAir == false && dy > 0) onAir = true;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		Collision::getInstance()->filterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 1.f;
		y += min_ty * dy + ny * 1.f;
		
		if (nx != 0) speed.vx = 0;
		if (ny != 0) speed.vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); ++i)
		{
			auto e = coEventsResult[i];

			if (dynamic_cast<Brick *>(e->obj))
			{
				if (e->ny < 0)
				{
					speed.vy = 0;
					onAir = false;
					state = stand;
				}
				else if (e->nx != 0)
				{
					speed.vx = 0;
				}
			}
		}
	}

	UINT size = coEvents.size();
	for (UINT i = 0; i < size; ++i) delete coEvents[i];
}

void MegamanX::collisionDynamic(unordered_map<int, CTreeObject*>* dynamicObjects)
{
	
}

MegamanX::MegamanX(UINT idTexture, float x, float y, float vx, float vy) :DynamicObject(idTexture, x, y, vx, vy)
{
	keyController = new KeyController(false);
	//state = stand;
	onAir = true;
}

MegamanX::~MegamanX()
{
}




MegamanX * MegamanX::clone(int id, int x, int y)
{
	return nullptr;
}

void MegamanX::update(DWORD dt, unordered_map<int, CTreeObject*>* staticObjects, unordered_map<int, CTreeObject*>* dynamicObjects)
{
	GameObject::update(dt);



	//speed.vy += 0.005f * dt;

	

	collisionStatic(staticObjects);
	collisionDynamic(dynamicObjects);
}

void MegamanX::updateState(DWORD dt) 
{
	int statePre = keyController->getState(isFlipX);
	if (state != statePre && statePre == dash)
	{
		_animations[statePre]->reset();
	}
	state = statePre;
	switch (state)
	{
	case stand:
	case shoot:
		speed.vx = 0;
		speed.vy = 0;
		break;
	case run:
	case run_shoot:
		(isFlipX) ? speed.vx = -0.1 : speed.vx = 0.1;
		(isKeyDown(DIK_X)) ? state = jump, speed.vy = -0.15 : state = run, speed.vy = 0;

		break;
	case dash:
	case dash_shoot:
		(isFlipX) ? speed.vx = -0.15 : speed.vx = 0.15;
		speed.vy = 0;
		break;
	case jump:
		speed.vy = -0.15;
		(isKeyDown(DIK_LEFTARROW) || isKeyDown(DIK_RIGHTARROW)) ? ((isFlipX) ? speed.vx = -0.1 : speed.vx - 0.1) : speed.vx = 0;
		break;
	case fall:
	case fall_shoot:
		speed.vy = 0.15;
		(isKeyDown(DIK_LEFTARROW) || isKeyDown(DIK_RIGHTARROW)) ? ((isFlipX) ? speed.vx = -0.05 : speed.vx - 0.05) : speed.vx = 0;
		break;
	case shock:
		speed.vx = 0;
		speed.vy = 0;
		break;
	default:
		break;
	}
}

void MegamanX::render(DWORD dt, D3DCOLOR colorBrush)
{
	updateState(dt);
	auto spriteHandler = gameGlobal->getSpriteHandler();
	spriteHandler->End();
	spriteHandler->Begin(D3DXSPRITE_DONOTSAVESTATE);
	auto center = cameraGlobal->transform(x, y);
	if (isFlipX)
		_animations[state]->renderFlipX(center.x, center.y, false, colorBrush);
	else
		_animations[state]->render(center.x, center.y, false, colorBrush);
	spriteHandler->End();
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

}


void MegamanX::onKeyDown(int keyCode)
{
	
	switch (keyCode)
	{
	case DIK_LEFT:
		keyController->addKeyArrow(true);
		break;
	case DIK_RIGHT:
		keyController->addKeyArrow(false);
		break;
	case DIK_Z:
		keyController->addKeyZ();
		break;
	case DIK_X:
		keyController->addKeyX();
		break;
	case DIK_C:
		keyController->addKeyC();
		break;
	default:
		break;
	}
}

void MegamanX::onKeyUp(int keyCode)
{
	
	switch (keyCode)
	{
	case DIK_LEFT:
		keyController->removeKeyArrow(true);
		break;
	case DIK_RIGHT:
		keyController->removeKeyArrow(false);
		break;
	case DIK_Z:
		keyController->removeKeyZ();
		break;
	case DIK_X:
		keyController->removeKeyX();
		break;
	case DIK_C:
		keyController->removeKeyC();
		break;
	default:
		break;
	}
}

void MegamanX::keyState(BYTE *_state)
{
	keyController->update();
}

void MegamanX::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = right;
	switch (state)
	{
	default:
		break;
	}

}
