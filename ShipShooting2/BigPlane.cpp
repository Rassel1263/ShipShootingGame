#include "DXUT.h"
#include "BigPlane.h"

BigPlane::BigPlane(D3DXVECTOR2 pos) : FlyingEnemy(pos)
{
    Resize(8);

    type = EnemyType::BigPlane;

	ability.SetAbility(100, 100);

    nowScene->player->fallowCamera = false;
    Camera::GetInstance().destCameraPos = pos;
    Camera::GetInstance().destDivideProj = 0.5f;

    nowScene->spawnBoss = true;

    for(int i = 0; i < 8; ++i)
        GetSprite(i).LoadAll(L"Assets/Sprites/enemy/typeboss2/" + std::to_wstring(i), 0.05f, false);

    bodies.clear();

    sGun.resize(24);

    for (int i = 0; i < 24; ++i)
        sGun[i].LoadAll(L"Assets/Sprites/enemy/Smallgun/" + std::to_wstring(i));

    bGun.resize(24);

    for (int i = 0; i < 24; ++i)
        bGun[i].LoadAll(L"Assets/Sprites/enemy/Biggun/" + std::to_wstring(i));

    sGunInfo.resize(12);

    int size = 48;
    for (int i = 0; i < 3; ++i)
        sGunInfo[i].ri.pos = pos + D3DXVECTOR2(-30 + i * size, 150);
    for (int i = 3; i < 6; ++i)
        sGunInfo[i].ri.pos = pos + D3DXVECTOR2(-30 + (i - 3) * size, -20);
    for (int i = 6; i < 9; ++i)
        sGunInfo[i].ri.pos = pos + D3DXVECTOR2(240 + (i - 6) * size, 150);
    for (int i = 9; i < 12; ++i)
        sGunInfo[i].ri.pos = pos + D3DXVECTOR2(240 + (i - 9) * size, -20);

    bGunInfo.resize(2);

    bGunInfo[0].ri.pos = pos + D3DXVECTOR2(460, 90);
    bGunInfo[1].ri.pos = pos + D3DXVECTOR2(-200, 90);


    outroTime = 10.0f;
    effectTime = 1.0f;
    restTime = 1.0f;
}

void BigPlane::Update(float deltaTime)
{
    if (Intro(deltaTime)) return;
    if (Outro(deltaTime)) return;

	Move(deltaTime);
    UpdatePattern(deltaTime);

    for (int i = 0; i < 12; ++i)
    {
        if (i < 2)
            SetWeaponRotate(bGunInfo[i], -nowScene->GetAngleFromTarget(bGunInfo[i].ri.pos, target->pos) + 450);

        SetWeaponRotate(sGunInfo[i], -nowScene->GetAngleFromTarget(sGunInfo[i].ri.pos, target->pos) + 450);
    }


    Unit::Update(deltaTime);
}

void BigPlane::Render()
{
    FlyingEnemy::Render();
}

void BigPlane::Destroy()
{
    nowScene->enemyManager.SortEnemy(this, type);
    destroy = true;
}

bool BigPlane::Move(float deltaTime)
{
	float targetAngle = D3DXToRadian(nowScene->GetAngleFromTarget(pos, target->pos));  // -90 ~ 270 
	float diff = targetAngle - curRadian;

	if (type == EnemyType::FlyingEnemy)
	{
		if (attackTimer >= attackTime)
			turnTime += deltaTime;
	}
	else
		turnTime += deltaTime;

	if (turnTime >= 0.01f)
	{
		if (diff > D3DX_PI)
			diff -= D3DX_PI * 2;
		else if (diff < -D3DX_PI)
			diff += D3DX_PI * 2;

		if (diff > turnSpeed)
			curRadian += turnSpeed;
		else if (diff < -turnSpeed)
			curRadian -= turnSpeed;
		else
		{
			Attack(deltaTime);
			curRadian = targetAngle;
		}

		turnTime = 0.0f;
	}

	SetAni(D3DXToDegree(-curRadian) + 450, true);

	pos += D3DXVECTOR2(cosf(curRadian), sinf(curRadian)) * ability.speed * deltaTime;

    return true;
}

void BigPlane::ChoosePattern()
{
    pattern = nowScene->GetRandomNumber(1, 3);
    shootInterval = 0.0f;
    gunIndex = 0;

    if (pattern == 1)
    {
        attackTime = 2.4f;
        attackSpeed = 0.2f;
    }
    else if (pattern == 2)
    {
        attackTime = 3.0f;
        attackSpeed = 0.5f;
    }
    else if (pattern == 3)
    {
        attackTime = 3.0f;
        attackSpeed = 0.3f;
    }
}

void BigPlane::UpdatePattern(float deltaTime)
{
    bool endPattern = false;

    if (pattern == 1)
        endPattern = Pattern1(deltaTime);
    else if (pattern == 2)
        endPattern = Pattern2(deltaTime);
    else if (pattern == 3)
        endPattern = Pattern3(deltaTime);

    if (!endPattern)
    {
        restTimer += deltaTime;

        if (restTimer >= restTime)
        {
            restTimer = 0.0f;
            attackTimer = 0.0f;

            ChoosePattern();
        }
    }
    else
        attackTimer += deltaTime;
}

void BigPlane::SetWeaponRotate(WeaponInfo& info, int rotate)
{
    int fixRotateScene = (int)((rotate / 15.0f)) % 24;
    info.gunRenderNum = (abs(fixRotateScene));
}

void BigPlane::WeaponRender(std::vector<Sprite>& weapon, std::vector<WeaponInfo>& weaponInfo)
{
}

bool BigPlane::Intro(float deltaTime)
{
	return false;
}

bool BigPlane::Outro(float deltaTime)
{
	return false;
}

bool BigPlane::Pattern1(float deltaTime)
{
    if (attackTimer >= attackTime)
        return false;

    shootInterval += deltaTime;

    if (shootInterval >= attackSpeed)
    {
        shootInterval = 0.0f;

        float angle = nowScene->GetAngleFromTarget(sGunInfo[gunIndex].ri.pos, target->pos);
        D3DXVECTOR2 fixPos = sGunInfo[gunIndex].ri.pos + D3DXVECTOR2(cosf(angle), sinf(angle)) * 20;

        nowScene->obm.AddObject(new MachinegunBullet(fixPos, target, L"enemy", 5, 1000));

        gunIndex++;
    }

    return true;
}

bool BigPlane::Pattern2(float deltaTime)
{
    if (attackTimer >= attackTime)
        return false;

    shootInterval += deltaTime;

    if (shootInterval >= attackSpeed)
    {
        nowScene->obm.AddObject(new AttackGuide(target->pos, D3DXVECTOR2(2, 2), 1.5f));
        shootInterval = 0.0f;
    }

    return true;
}

bool BigPlane::Pattern3(float deltaTime)
{
    if (attackTimer >= attackTime)
        return false;

    shootInterval += deltaTime;

    if (shootInterval >= attackSpeed)
    {
        D3DXVECTOR2 fixPos = pos + D3DXVECTOR2(nowScene->GetRandomNumber(-400, 400), 0);
        nowScene->obm.AddObject(new HomingBullet(fixPos, target, CBullet::BulletType::Torpedo, L"enemy", 15, nowScene->GetRandomNumber(0, 360), 0.0f));

        shootInterval = 0.0f;
    }

    return true;
}
