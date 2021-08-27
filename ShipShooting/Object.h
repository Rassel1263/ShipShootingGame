#pragma once

class Object
{
public:
	bool destroy = false;
	bool bCollider = false;
	D3DXVECTOR2 pos = { 0, 0 };
	int layer = 0;
	std::vector<Collider> bodies;

	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void OnCollision(Collider& coll);
};

class ObjectManager
{
	std::vector<Object*> objects;
	std::vector<Object*> addObjects;
public:
	~ObjectManager();

	void AddObject(Object* obj);
	void Collision();
	void Update(float deltaTime);
	void Render();
};
