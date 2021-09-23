#include "DXUT.h"
#include "BigPlane.h"
#include "BossIntro.h"

BigPlane::BigPlane(D3DXVECTOR2 pos) : FlyingEnemy(pos)
{
    type = EnemyType::BigPlane;

    this->airPos = this->pos.y;
    this->pos.y += 1000;

    Camera::GetInstance().destCameraPos = D3DXVECTOR2(pos.x, airPos);
    Camera::GetInstance().destDivideProj = 0.7f;

    nowScene->spawnBoss = true;
    nowScene->obm.AddObject(new BossIntro());

    Resize(8);
    for(int i = 0; i < 8; ++i)
        GetSprite(i).LoadAll(L"Assets/Sprites/enemy/typeboss2/" + std::to_wstring(i), 0.05f, false);


    bodies.clear();

	ability.SetAbility(1000, 100);

    renderNum = 4;

    attackTimer = 0.0f;
    attackTime = 0.0f;

    outroTime = 10.0f;
    effectTime = 1.0f;
    restTime = 1.0f;
}

void BigPlane::Update(float deltaTime)
{
    if (Intro(deltaTime)) return;
    if (Outro(deltaTime)) return;

    if (setAirPos)
        pos.y = airPos;

    UpdatePattern(deltaTime);

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
	float targetAngle = D3DXToRadian(nowScene->GetAngleFromTarget(D3DXVECTOR2(pos.x, airPos), target->pos));  // -90 ~ 270 
	float diff = targetAngle - curRadian;

	
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
			curRadian = targetAngle;

		turnTime = 0.0f;
	}

	SetAni(D3DXToDegree(-curRadian) + 450, true);

	pos.x += cosf(curRadian) * ability.speed * deltaTime;
    airPos += sinf(curRadian)* ability.speed * deltaTime;

    return true;
}

void BigPlane::Hit(float damage)
{
    if (intro) return;

    CEnemy::Hit(damage);
}

void BigPlane::ChoosePattern()
{
    pattern = 3;
    shootInterval = 0.0f;

    if (pattern == 1)
    {
        attackTime = 5.0f;
        attackSpeed = 0.2f;
    }
    else if (pattern == 2)
    {
        attackTime = 3.0f;
        attackSpeed = 0.05f;
    }
    else if (pattern == 3)
    {
        attackTime = 4.0f;
        attackSpeed = 1.0f;
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

bool BigPlane::Intro(float deltaTime)
{
    if (!intro) return false;

    if (pos.y >= airPos)
        pos.y -= 250 * deltaTime;
    else
    {
        CreateCollider(D3DXVECTOR2(-300, -300), D3DXVECTOR2(300, 300), L"enemy");
        intro = false;
    }


	return true;
}

bool BigPlane::Outro(float deltaTime)
{

    if (ability.hp <= 0)
    {
        Camera::GetInstance().destDivideProj = 1.5f;
        Camera::GetInstance().destCameraPos = pos;

        hit = false;
        nowScene->player->stop = true;
        nowScene->stopTime = true;

        outroTime -= deltaTime;
        effectTimer += deltaTime;

        if (outroTime <= 0.0f)
        {
            Camera::GetInstance().destDivideProj = 1.0f;

            GetNowSprite().color.a -= deltaTime;

            if (GetNowSprite().color.a <= 0.0f)
            {
                nowScene->player->stop = false;
                nowScene->player->fallowCamera = true;
                nowScene->obm.AddObject(new StageFont(StageFont::Type::CLEAR));
                Destroy();
            }

        }
        else
        {
            if (effectTimer >= effectTime)
            {
                nowScene->obm.AddObject(new Effect(L"onexplode", pos + nowScene->GetRandomVector(-500, 500, -300, 300), D3DXVECTOR2(0.5, 0.5), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f));

                effectTime -= 0.05f;
                effectTimer = 0.0f;

                Camera::GetInstance().cameraQuaken = D3DXVECTOR2(10, 10);
            }
        }

        return true;
    }

	return false;
}

bool BigPlane::Pattern1(float deltaTime)
{
    Move(deltaTime);

    shootInterval += deltaTime;

    if (shootInterval >= attackSpeed)
    {
        int size = nowScene->GetRandomNumber(1, 4);
        D3DXVECTOR2 targetPos = pos + nowScene->GetRandomVector(-1200, 1200, -700, 700);

        auto lambda = [=] 
        {
            nowScene->obm.AddObject(new Effect(L"onexplode", targetPos, D3DXVECTOR2(0.3, 0.3) * size, D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f));
            nowScene->obm.AddObject(new AttackCollider(targetPos, D3DXVECTOR2(-50, -50), D3DXVECTOR2(50, 50), 20, 0.1f));  
            Camera::GetInstance().cameraQuaken = D3DXVECTOR2(3, 3) * size;
        };

        nowScene->obm.AddObject(new AttackGuide(targetPos, D3DXVECTOR2(size, size), nowScene->GetRandomNumber(10, 20) * 0.1f, 1, lambda));
        shootInterval = 0.0f;
    }

    if (attackTimer >= attackTime)
        return false;

    return true;
}

bool BigPlane::Pattern2(float deltaTime)
{
    shootInterval += deltaTime;

    if (shootInterval >= attackSpeed)
    {
        int index = nowScene->GetRandomNumber(1, 3);
        
        if (index == 1)
            nowScene->obm.AddObject(new MachinegunBullet(pos, target, L"enemy", 5, nowScene->GetRandomNumber(4, 7) * 100));
        else if(index == 2)
            nowScene->obm.AddObject(new HomingBullet(pos, target, CBullet::BulletType::Torpedo, L"enemy", 5, nowScene->GetRandomNumber(0, 360), nowScene->GetRandomNumber(5, 10) * 100));
        else if(index == 3)
            nowScene->obm.AddObject(new HomingBullet(pos, target, CBullet::BulletType::Missile, L"enemy", 5, nowScene->GetRandomNumber(0, 360), nowScene->GetRandomNumber(5, 10) * 100));

        shootInterval = 0.0f;
    }

    if (attackTimer >= attackTime)
        return false;

    return true;
}

bool BigPlane::Pattern3(float deltaTime)
{
    shootInterval += deltaTime;

    if (shootInterval >= attackSpeed)
    {
        D3DXVECTOR2 targetPos = D3DXVECTOR2(Camera::GetInstance().cameraPos.x, target->pos.y + nowScene->GetRandomNumber(-200, 200));

        auto lambda = [=]
        {
            nowScene->obm.AddObject(new AttackCollider(targetPos, D3DXVECTOR2(-1200, -90), D3DXVECTOR2(1200, 90), 20, 0.1f));
            Camera::GetInstance().cameraQuaken = D3DXVECTOR2(8, 8);
        };

        nowScene->obm.AddObject(new AttackGuide(targetPos, D3DXVECTOR2(1, 1), 2.0f, 2, lambda));

        shootInterval = 0.0f;
    }

    if (attackTimer >= attackTime)
        return false;


    return true;
}
