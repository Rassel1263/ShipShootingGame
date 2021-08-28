#include "Header.h"
#include "Player.h"
#include "HomingBullet.h"
#include "MachineGun.h"
#include "Cannon.h"

Player::Player()
{
	spr.LoadAll(L"Assets/Sprites/Unit/Player/Ship");
	pos.y = -200;

	SetAbility(100, 300);
	nowScene->obm.AddObject(machineGun = new MachineGun(this, D3DXVECTOR2(0, 26)));
	nowScene->obm.AddObject(cannon = new Cannon(this, D3DXVECTOR2(0, -25)));
}

void Player::Update(float deltaTime)
{
	Move(deltaTime);
	SetWeaponPos();

	if (Input::GetInstance().KeyPress('Q'))
		machineGun->Shoot();

	if (Input::GetInstance().KeyPress('W'))
		cannon->Shoot();

	if (Input::GetInstance().KeyDown(VK_SPACE))
		nowScene->obm.AddObject(new HomingBullet(pos));

	spr.Update(deltaTime);
}

void Player::Render()
{
	ri.pos = pos;
	spr.Render(ri);	
}

bool Player::Move(float deltaTime)
{
	D3DXVECTOR2 moveDir = { 0, 0 };

	if (ability.speed < 300)
		ability.speed += 150 * deltaTime;

	if (Input::GetInstance().KeyPress(VK_DOWN))
	{
		if(ability.speed > 200)
			ability.speed -= 200 * deltaTime;
	}
	if (Input::GetInstance().KeyPress(VK_RIGHT))
		moveDir.x = 1;
	if (Input::GetInstance().KeyPress(VK_LEFT))
		moveDir.x = -1;

	D3DXVec2Normalize(&moveDir, &moveDir);

	if (moveDir.x == 0) return false;

	pos += moveDir * ability.speed * deltaTime;

	return true;
}

void Player::SetWeaponPos()
{
	machineGun->pos = pos + machineGun->offset;
	cannon->pos = pos + cannon->offset;
}
