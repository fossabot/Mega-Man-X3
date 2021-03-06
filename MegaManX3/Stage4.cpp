#include "Stage4.h"
Stage4::Stage4()
{
	gate = new Gate(2288, 896, 16, 48, false);
	gate->state = GateLock;
	gateBox = gate->getBoundBox();
}


Stage4::~Stage4()
{
}

void Stage4::getStaticObjects(unordered_map<int, GameObject*>* saticObjects)
{
}

void Stage4::getDynamicObjects(unordered_map<int, GameObject*>* dynamicObjects)
{
}

void Stage4::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects)
{
	if(gateBox.intersectsWith(*viewPortGlobal))
	{
		draw = true;
		if (!alreadyOpenGate && (gateBox.intersectsWith(mainGlobal->getBoundBox())
			||
			main->collisionGameObject(main, gate)))
		{
			gate->state = GateOpening;
			alreadyOpenGate = true;
			main->enable = false;
			main->speed.vx = 0.005f * dt;
		}
	}
	else draw = false;
	if (!main->enable && gate->state == GateOpen)
	{
		updateMain(dt);
	}
}

void Stage4::render(DWORD dt, D3DCOLOR colorBrush)
{
	if (draw)
		gate->render(dt);
}

void Stage4::reset()
{
	gate->state = GateLock;
	alreadyOpenGate = false;
}
