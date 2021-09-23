#include "DXUT.h"
#include "BigShip.h"
#include "BossIntro.h"

BigShip::BigShip(D3DXVECTOR2 pos) : FloatingEnemy(pos)
{
    type = EnemyType::BigShip;

    Camera::GetInstance().destCameraPos = pos;
    Camera::GetInstance().destDivideProj = 0.7f;

    nowScene->spawnBoss = true;
 
    nowScene->obm.AddObject(new BossIntro());

    Resize(2);
    GetSprite(0).LoadAll(L"Assets/Sprites/enemy/typeboss1/enter", 0.05f, false);
    GetSprite(1).LoadAll(L"Assets/Sprites/enemy/typeboss1/move", 0.05f, true);

    sGun.resize(24);

    for (int i = 0; i < 24; ++i)
        sGun[i].LoadAll(L"Assets/Sprites/enemy/Smallgun/" + std::to_wstring(i));

    bGun.resize(24);

    for(int i = 0; i < 24; ++i)
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

    bodies.clear();

    ability.SetAbility(500, 100);

    attackTimer = 0.0f;
    attackTime = 0.0f;

    outroTime = 10.0f;
    effectTime = 1.0f;
    restTime = 1.0f;
}

void BigShip::Update(float deltaTime)
{
    if (Intro(deltaTime)) return;
    if (Outro(deltaTime)) return;

    UpdatePattern(deltaTime);

    for (int i = 0; i < 12; ++i)
    {
        if(i < 2)
            SetWeaponRotate(bGunInfo[i], -nowScene->GetAngleFromTarget(bGunInfo[i].ri.pos, target->pos) + 450);

        SetWeaponRotate(sGunInfo[i], -nowScene->GetAngleFromTarget(sGunInfo[i].ri.pos, target->pos) + 450);
    }

    Unit::Update(deltaTime);
}

void BigShip::Render()
{
    FloatingEnemy::Render();

    if (!intro)
    {
        WeaponRender(sGun, sGunInfo);
        WeaponRender(bGun, bGunInfo);
    }
}

void BigShip::Hit(float damage)
{
    if (intro) return;

    CEnemy::Hit(damage);
}

void BigShip::Destroy()
{
    nowScene->enemyManager.SortEnemy(this, type);
    destroy = true;
}

void BigShip::ChoosePattern()
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

void BigShip::UpdatePattern(float deltaTime)
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


void BigShip::SetWeaponRotate(WeaponInfo& bi ,int rotate)
{
    int fixRotateScene = (int)((rotate / 15.0f)) % 24;
    bi.gunRenderNum = (abs(fixRotateScene));
}

void BigShip::WeaponRender(std::vector<Sprite>& weapon, std::vector<WeaponInfo>& weaponInfo)
{
    int size = weaponInfo.size();
    for (int i = 0; i < size; ++i)
    {
        weapon[weaponInfo[i].gunRenderNum].Render(weaponInfo[i].ri);
    }
}

bool BigShip::Intro(float deltaTime)
{
    if (!intro)
        return false;

    if (!GetSprite(0).bAnimation)
    {
        GetNowSprite().Reset();
        SetAni(1);
        intro = false;
        CreateCollider(D3DXVECTOR2(-500, -500), D3DXVECTOR2(500, 500), L"enemy");
    }

    GetNowSprite().Update(deltaTime);

    return true;
}

bool BigShip::Outro(float deltaTime)
{
    if (ability.hp <= 0)
    {
        Camera::GetInstance().destDivideProj = 1.5f;

        hit = false;
        Camera::GetInstance().destCameraPos = pos;
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

bool BigShip::Pattern1(float deltaTime)
{
    shootInterval += deltaTime;

    if (shootInterval >= attackSpeed)
    {
        shootInterval = 0.0f;

        float angle = nowScene->GetAngleFromTarget(sGunInfo[gunIndex].ri.pos, target->pos);
        D3DXVECTOR2 fixPos = sGunInfo[gunIndex].ri.pos + D3DXVECTOR2(cosf(angle), sinf(angle)) * 20;

        nowScene->obm.AddObject(new MachinegunBullet(fixPos, target, L"enemy", 5, 1000));

        gunIndex++;
    }

    if (attackTimer >= attackTime)
        return false;


    return true;
}

bool BigShip::Pattern2(float deltaTime)
{
    shootInterval += deltaTime;

    if (shootInterval >= attackSpeed)
    {
        D3DXVECTOR2 targetPos = target->pos;
        auto lambda = [=] 
        {
            nowScene->obm.AddObject(new Effect(L"onexplode", targetPos, D3DXVECTOR2(0.3, 0.3), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f));
            nowScene->obm.AddObject(new AttackCollider(targetPos, D3DXVECTOR2(-50, -50), D3DXVECTOR2(50, 50), 20, 0.1f));  
        };

        nowScene->obm.AddObject(new AttackGuide(targetPos, D3DXVECTOR2(2, 2), 1.5f, 1, lambda));
        shootInterval = 0.0f;
    }

    if (attackTimer >= attackTime)
        return false;

    return true;
}

bool BigShip::Pattern3(float deltaTime)
{
    shootInterval += deltaTime;

    if (shootInterval >= attackSpeed)
    {
        D3DXVECTOR2 fixPos = pos + D3DXVECTOR2(nowScene->GetRandomNumber(-400, 400), 0);
        nowScene->obm.AddObject(new HomingBullet(pos, target, CBullet::BulletType::Torpedo, L"enemy", 15, nowScene->GetRandomNumber(0, 360), 0.0f));

        shootInterval = 0.0f;
    }

    if (attackTimer >= attackTime)
        return false;

    return true;
}
