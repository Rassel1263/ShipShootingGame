#include "DXUT.h"
#include "Scene.h"

float Scene::score = 0.0f;

void Scene::Init()
{
}

void Scene::Update(float deltaTime)
{
	if (Input::GetInstance().KeyDown(VK_F1))
		player->god = !player->god;

	if (Input::GetInstance().KeyDown(VK_F3))
		stopTime = !stopTime;

	if (Input::GetInstance().KeyDown(VK_F4))
		Game::GetInstance().ChangeScene(new MainScene());

	if (Input::GetInstance().KeyDown(VK_F5))
		Game::GetInstance().ChangeScene(new GameScene());

	if (Input::GetInstance().KeyDown(VK_F6))
		Game::GetInstance().ChangeScene(new GameScene2());
	
	if(Input::GetInstance().KeyDown(VK_F7))
		Game::GetInstance().ChangeScene(new RankingScene());

	obm.Collision();
	obm.Update(deltaTime);
}

void Scene::Render()
{
	obm.Render();
}

void Scene::UIRender()
{
	obm.UIRender();
}

void Scene::LoadAll()
{
	ShaderManager::GetInstance().CreateEffect("Color", L"Assets/Shader/ColorShader.fx", 1);
	ShaderManager::GetInstance().CreateEffect("Blink", L"Assets/Shader/BlinkShader.fx", 1);

	// BGM
	SoundManager::GetInstance().Create(L"main", L"Assets/Sound/BGM/main.mp3", 1);
	SoundManager::GetInstance().Create(L"stage1", L"Assets/Sound/BGM/stage1.mp3", 1);
	SoundManager::GetInstance().Create(L"stage2", L"Assets/Sound/BGM/stage2.mp3", 1);
	SoundManager::GetInstance().Create(L"boss", L"Assets/Sound/BGM/boss.mp3", 1);
	SoundManager::GetInstance().Create(L"win", L"Assets/Sound/BGM/win.mp3", 1);

	// UI
	SoundManager::GetInstance().Create(L"clickBtn", L"Assets/Sound/Btn/ClickBtn.mp3", 1);
	SoundManager::GetInstance().Create(L"moveBtn", L"Assets/Sound/Btn/MoveBtn.mp3", 1);

	// Enemy
	SoundManager::GetInstance().Create(L"explo", L"Assets/Sound/Enemy/explo.mp3", 1);
	SoundManager::GetInstance().Create(L"bossIntro", L"Assets/Sound/Enemy/bossIntro.mp3", 1);

	// Player
	SoundManager::GetInstance().Create(L"machinegun", L"Assets/Sound/Player/gun.mp3", 5);
	SoundManager::GetInstance().Create(L"navalgun", L"Assets/Sound/Player/navalgun.mp3", 5);
	SoundManager::GetInstance().SetVolume(L"navalgun", 200);
	SoundManager::GetInstance().Create(L"missile", L"Assets/Sound/Player/missile.mp3", 5);
	SoundManager::GetInstance().Create(L"airVoi", L"Assets/Sound/Player/airStart.mp3", 5);
	SoundManager::GetInstance().Create(L"airMove", L"Assets/Sound/Player/airMove.mp3", 5);
	SoundManager::GetInstance().Create(L"airBoom", L"Assets/Sound/Player/airBoom.mp3", 5);

	// Effect
	SoundManager::GetInstance().Create(L"item", L"Assets/Sound/Effect/Item.mp3", 1);
	SoundManager::GetInstance().Create(L"reload", L"Assets/Sound/Effect/reload.mp3", 1);
	SoundManager::GetInstance().Create(L"msg1", L"Assets/Sound/Effect/msg.mp3", 1);
	SoundManager::GetInstance().Create(L"msg2", L"Assets/Sound/Effect/msg2.mp3", 1);
	SoundManager::GetInstance().Create(L"msg3", L"Assets/Sound/Effect/msg3.mp3", 1);
	SoundManager::GetInstance().Create(L"skillMsg", L"Assets/Sound/Effect/skillMsg.mp3", 1);
	SoundManager::GetInstance().Create(L"start", L"Assets/Sound/Effect/start.mp3", 1);
}

void Scene::AddScore(int score)
{
	destScore += score;
}

int Scene::GetRandomNumber(int min, int max)
{
	std::default_random_engine rnd(rd());
	std::uniform_int_distribution<int> dis(min, max);

	return dis(rnd);
}

float Scene::GetAngleFromTarget(D3DXVECTOR2 pos, D3DXVECTOR2 targetPos)
{
	D3DXVECTOR2 distance = targetPos - pos;
	return D3DXToDegree(atan2(distance.y, distance.x));
}

D3DXVECTOR2 Scene::GetRandomVector(int minX, int maxX, int minY, int maxY)
{
	std::default_random_engine rnd(rd());
	std::uniform_int_distribution<int> x(minX, maxX);
	std::uniform_int_distribution<int> y(minY, maxY);

	return D3DXVECTOR2((float)x(rnd), (float)y(rnd));
}
