#include "Header.h"
#include "HomingBullet.h"

HomingBullet::HomingBullet(D3DXVECTOR2 pos) : CBullet(pos)
{
}

void HomingBullet::Update(float deltaTime)
{
	homingTime += deltaTime;
	if (homingTime >= 0.05f)
	{
		D3DXVECTOR2 distance = nowScene->enemy->pos - pos;
		D3DXVec2Normalize(&distance, &distance);
		angle = atan2(distance.y, distance.x);

		float diff = angle - rotate;
		float turnSpeed = D3DXToRadian(3);

		/*if (diff >= D3DX_PI)
			diff -= D3DX_PI;

		if (diff <= -D3DX_PI)
			diff += D3DX_PI;*/

		if (diff > turnSpeed)
			rotate += turnSpeed;
		else if (diff < -turnSpeed)
			rotate -= turnSpeed;
		else
			rotate = turnSpeed;

		homingTime = 0.0f;
	}

	pos += D3DXVECTOR2(cosf(rotate), sinf(rotate)) * 300 * deltaTime;
	ri.rotate = D3DXToDegree(-rotate);
}

void HomingBullet::Render()
{
	CBullet::Render();
}
