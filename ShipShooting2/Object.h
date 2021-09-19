#pragma once

class Object
{
public:
	bool destroy = false;
	bool bCollider = false;
	bool bCamera = true;
	D3DXVECTOR2 pos = { 0, 0 };
	int layer = 0;
	std::vector<Collider> bodies;

	virtual ~Object() {}

	void CreateCollider(D3DXVECTOR2 min, D3DXVECTOR2 max, std::wstring tag, D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 0, 0));
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void OnCollision(Collider& coli);
};

class ObjectUI
{
public:
	bool destroy = false;
	D3DXVECTOR2 pos = { 0, 0 };
	int layer = 0;

	virtual ~ObjectUI() {}

	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void OnCollision(Collider& coli);
};

class ObjectManager
{
private:
	std::vector<Object*> objects;
	std::vector<Object*> addObjects;
	std::vector<ObjectUI*> uiObjects;
	std::vector<ObjectUI*> addUIObjects;

public:
	~ObjectManager();

	void AddObject(Object* obj);
	void AddObject(ObjectUI* obj);

	void Collision();
	void Update(float deltaTime);
	void Render();
	void UIRender();
};

