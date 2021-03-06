#include "Camera.h"


void Camera::switchState()
{
	switch (nAnimation)
	{
	case 2:
		if (viewport.x >= 768)
			aniSwitchState = false, viewport.x = 768;
		else viewport.x += 4;
		break;
	case 3:
		if (viewport.y <= 0)
			aniSwitchState = false;
		else viewport.y -= 1;
		break;
	case 4:
		if (viewport.x >= 1024)
			aniSwitchState = false, viewport.x = 1024;
		else viewport.x += 4;
		break;
	case 5:
		if (viewport.x >= 2304)
			aniSwitchState = false, viewport.x = 2304;
		else viewport.x += 4;
		break;
	case 6:
		if (viewport.x >= 2560)
			aniSwitchState = false, viewport.x = 2560;
		else viewport.x += 4;
		break;
	case 7:
		if (viewport.x >= 5632)
			aniSwitchState = false, viewport.x = 5632;
		else viewport.x += 4;
		break;
	case 8:
		if(viewport.x >= 5888)
			aniSwitchState = false, viewport.x = 5888;
		else viewport.x += 4;
		break;
	case 9:
		if (viewport.x >= 7424)
			aniSwitchState = false, viewport.x = 7424;
		else viewport.x += 4;
		break;
	case 10:
		if (viewport.x >= 7680)
			aniSwitchState = false, viewport.x = 7680;
		else viewport.x += 4;
		break;
	default:
		break;
	}
}

//start
void Camera::state1(int cameraX, int cameraY)
{
	if (cameraX > maxValue)
	{
		blockBackward = new Block(ID_BLOCK_BACK_WARD, 736, 512, 32, 256);
		nextAnimation();
		lockLeft = true;
		lockTop = true;
		minValue = 0;
		maxValue = 512;
		state = &Camera::state2;
	}
	else
		if (cameraX <= minValue)
		{
			if (lockLeft) return;

			lockLeft = true;
			viewport.x = minValue;
		}
		else if (lockLeft)
			lockLeft = false;
}

//elevator
void Camera::state2(int cameraX, int cameraY)
{
	if (cameraY < minValue + 32)
	{
		delete blockBackward;
		blockBackward = null;
		nextAnimation();
		lockTop = true;
		minValue = 768;
		maxValue = 896;
		state = &Camera::state3;
	}else
		if (cameraY >= maxValue - 64)
		{
			if (viewport.y + 5 < maxValue)
				viewport.y += 5;
			else viewport.y = maxValue;
			if (lockTop) return;
			lockTop = true;
			//viewport.y = maxValue;
		}
		else 
			if (lockTop)
			{
				if (cameraY - viewport.y < 0)
					viewport.y -= 4;
				else
					lockTop = false;
			}
}

//top elevator
void Camera::state3(int cameraX, int cameraY)
{
	if (cameraX > maxValue)
	{
		blockBackward = new Block(ID_BLOCK_BACK_WARD, 992, 0, 32, 256);
		nextAnimation();
		lockTop = true;
		lockLeft = true;
		minValue = 1024;
		maxValue = 2172;
		state = &Camera::state4;
		return;
	}
	if (cameraX <= minValue)
	{
		if (lockLeft) return;

		lockLeft = true;
		viewport.x = minValue;
	}
	else if (lockLeft)
		lockLeft = false;
}

//run to mini boss 1
void Camera::state4(int cameraX, int cameraY)
{
	if (cameraX > maxValue)
	{
		delete blockBackward;
		blockBackward = new Block(ID_BLOCK_BACK_WARD, 2297, 895, 22, 52);
		nextAnimation();
		lockTop = true;
		lockLeft = true;
		minValue = 2432;
		maxValue = 2432;
		state = &Camera::state5;
		return;
	}
	if (!lockLeft && cameraX > maxValue - 128)
	{
		lockLeft = true;
	}

	if (cameraX < minValue)
	{
		if (!lockLeft)
		{
			lockLeft = true;
			viewport.x = minValue;
		}
		return;
	}
	if (cameraX < 1536 && cameraY > 128)
	{
		if (!lockLeft)
		{
			lockLeft = true;
			viewport.x = 1536;
		}
	}
	else if (lockLeft && cameraX <= maxValue - 128) lockLeft = false;

	if (cameraY <= 64 || cameraY >= 640)
	{
		if (cameraY > 640)
		{
			if (viewport.y + 5 < 768)
				viewport.y += 5;
			else viewport.y = 768;
		}
		if (lockTop) return;

		lockTop = true;
		//viewport.y = cameraY < 64 ? 0 : 768;
	}
	else 
		if (lockTop)
		{
			if (cameraY > 64 && cameraY < 256 && viewport.y - cameraY < 0)
				viewport.y += 10;
			else if (cameraY < 640 && viewport.y - cameraY > 0)
				viewport.y -= 5;
			else
				lockTop = false;
		}
}

//mini boss 1
void Camera::state5(int cameraX, int cameraY)
{
	if (cameraX > maxValue) //next
	{
		delete blockBackward;
		blockBackward = new Block(ID_BLOCK_BACK_WARD, 2546, 895, 22, 52);
		nextAnimation();
		lockTop = true;
		lockLeft = true;
		minValue = 2560;
		maxValue = 5504;
		state = &Camera::state6;
		return;
	}
	//if (viewport.y < 768) viewport.y = 768;
}

//mini bosss 2
void Camera::state6(int cameraX, int cameraY)
{
	if (cameraX > maxValue)
	{
		delete blockBackward;
		blockBackward = new Block(ID_BLOCK_BACK_WARD, 5632, 895, 13, 61);
		nextAnimation();
		lockTop = true;
		lockLeft = true;
		minValue = 5632;
		maxValue = 5760;
		state = &Camera::state7;
		return;
	}
	if (!lockLeft && cameraX > maxValue - 128)
		lockLeft = true;
	if (cameraX <= minValue)
	{
		if (!lockLeft) 
		{
			lockLeft = true;
			viewport.x = minValue;
		}
	}
	else if (lockLeft && cameraX <= maxValue - 128)
		lockLeft = false;


	if (cameraY <= 576)
	{
		if (viewport.y > 512)
			viewport.y -= 5;
		else viewport.y = 512;

		if (lockTop) return;
		lockTop = true;
	}

	if (cameraY >= 672)
	{
		if(viewport.y + 5 < 768)
			viewport.y += 5;
		else viewport.y = 768;

		if (lockTop)
			return;
		lockTop = true;
	}
	else if (lockTop)
	{
		if (cameraX < 2816) {
			lockTop = true;
			return;
		}
		if ( cameraY < 672 && viewport.y - cameraY > 0)
			viewport.y -= 5;
		else if(cameraY >= 576)
		lockTop = false;
	}

}

//bit or byte
void Camera::state7(int cameraX, int cameraY)
{
	if (cameraX > maxValue)
	{
		delete blockBackward;
		blockBackward = new Block(ID_BLOCK_BACK_WARD, 5890, 895, 10, 61);
		nextAnimation();
		lockTop = true;
		lockLeft = true;
		minValue = 5888;
		maxValue = 7296;
		state = &Camera::state8;
		return;
	}
}

//run to wait boss
void Camera::state8(int cameraX, int cameraY)
{
	if (cameraX > maxValue)
	{
		delete blockBackward;
		blockBackward = new Block(ID_BLOCK_BACK_WARD, 7412, 1663, 16, 66);
		nextAnimation();
		lockTop = true;
		lockLeft = true;
		minValue = 7296;
		maxValue = 7552;
		state = &Camera::state9;
		return;
	}
	if (!lockLeft && cameraX > maxValue - 128)
		lockLeft = true;
	if ((cameraX <= minValue) || (cameraX < 6144 && cameraY < 1472))
	{
		if (!lockLeft)
		{
			lockLeft = true;
			viewport.x = minValue;
		}
	}
	else if (lockLeft && cameraX <= maxValue - 128)
		lockLeft = false;

	if (cameraY <= 800)
	{
		if(viewport.y <= 768)
			viewport.y += 4;

		if (viewport.y >= 768)
			viewport.y -= 4;
		if (!lockTop)
		{
			lockTop = true;
		}
		return;
	}

	if(cameraX > minValue && cameraY > 1408)
	{
		viewport.y = 1536;
		if (!lockTop)
		{
			lockTop = true;
		}
		return;
	}

	if(cameraX <= minValue && cameraY >= 1472)
	{
		if (viewport.y + 4 <= 1536)
			viewport.y += 4;
		else viewport.y = 1536;

		if (!lockTop)
		{
			lockTop = true;
		}
	}
	else if (lockTop)
	{
		if (cameraY < 1472 && viewport.y - cameraY > 0)
			viewport.y -= 5;
		else
			lockTop = false;
	}
}

// wait boss
void Camera::state9(int cameraX, int cameraY)
{
	if (cameraX > maxValue)
	{
		delete blockBackward;
		blockBackward = new Brick(ID_BLOCK_BACK_WARD, 7680, 1662, 14, 80);
		nextAnimation();
		lockTop = true;
		lockLeft = true;
		minValue = 7424;
		maxValue = 7552;
		state = &Camera::state10;
		return;
	}
}

// boss
void Camera::state10(int cameraX, int cameraY)
{
	//viewport.x = 7680;
}

Camera::Camera(int x, int y, int width, int height) : viewport(x, y, width, height)
{
	viewport.x = (x / 256) * 256;
	viewport.y = (y / 256) * 256;
	//1
	nAnimation = 1;
	state = &Camera::state1;
	minValue = 0;
	maxValue = 650;
	lockTop = true;
	lockLeft = true;

	//2
	//nAnimation = 2;
	//aniSwitchState = true;
	//state = &Camera::state2;
	//lockTop = true;
	//lockLeft = true;
	//minValue = 0;
	//maxValue = 512;
	
	//before shuriken
	//nAnimation = 4;
	//state = &Camera::state4;
	//minValue = 1024;
	//maxValue = 2172;
	//lockTop = true;
	//lockLeft = true;

	////shuriken
	//nAnimation = 5;
	//state = &Camera::state5;
	//maxValue = 2432;
	//minValue = 2432;
	//lockTop = true;
	//lockLeft = true;
	//
	//after shuriken
	//nAnimation = 6;
	//state = &Camera::state6;
	//minValue = 2560;
	//maxValue = 5504;
	//lockTop = true;
	//lockLeft = true;

	//after byte
	//nAnimation = 8;
	//state = &Camera::state8;
	//minValue = 5888;
	//maxValue = 7296;
	//lockTop = true;
	//lockLeft = true;

	////boss
	//nAnimation = 10;
	//lockTop = true;
	//lockLeft = true;
	//minValue = 7424;
	//maxValue = 7552;
	//state = &Camera::state10;
}

void Camera::update(int x, int y) //center x, center y
{
	if (aniSwitchState)
	{
		switchState();
		return;
	}
	if (!enable) return;

	int cameraX = x - 128;
	int cameraY = y - 128;

	(this->*state)(cameraX, cameraY);

	if (!lockLeft) //don't lock camera x
		viewport.x = cameraX;

	if(!lockTop) //don't lock camera y
		viewport.y = cameraY;
}

void Camera::nextAnimation()
{
	nAnimation += 1;
	aniSwitchState = true;
}

const Point Camera::transform(const int& x, const int& y) const
{
	return { x - viewport.x, y - viewport.y };
}

void Camera::resetState()
{
	aniSwitchState = false;
	if (nAnimation < 6)
	{
		nAnimation = 1;
		state = &Camera::state1;
		minValue = 0;
		maxValue = 650;
		lockTop = true;
		lockLeft = false;
		mainGlobal->x = viewport.x = 100;
		mainGlobal->y = 512;
		viewport.y = 512;
		if(blockBackward)
			delete blockBackward,
			blockBackward = null;
	}
	else if (nAnimation <= 7)
	{
		nAnimation = 6;
		state = &Camera::state6;
		minValue = 2560;
		maxValue = 5504;
		lockTop = true;
		lockLeft = false;
		if (blockBackward)
			delete blockBackward;

		blockBackward = new Block(ID_BLOCK_BACK_WARD, 2546, 895, 22, 52);

		mainGlobal->x = viewport.x = 2600;
		mainGlobal->y = 760;
		viewport.y = 768;

		mainGlobal->x = 4704;
	}
	else if (nAnimation < 9)
	{
		nAnimation = 8;
		lockTop = true;
		lockLeft = true;
		minValue = 5888;
		maxValue = 7296;
		state = &Camera::state8;


		mainGlobal->x = 5910;
		viewport.x = 5888;
		mainGlobal->y = 760;
		viewport.y = 768;
		if (blockBackward)
			delete blockBackward;
		blockBackward = new Block(ID_BLOCK_BACK_WARD, 5890, 895, 10, 61);
	}
	else
	{
		nAnimation = 9;
		lockTop = true;
		lockLeft = true;
		minValue = 7296;
		maxValue = 7552;
		state = &Camera::state9;
	
		mainGlobal->x = 7460;
		viewport.x = 7424;
		mainGlobal->y = 1525;
		viewport.y = 1536;

		if (blockBackward)
			delete blockBackward;
		blockBackward = new Block(ID_BLOCK_BACK_WARD, 7412, 1663, 16, 66);
	}
}

