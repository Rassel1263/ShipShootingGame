#include "Header.h"
#include "Object.h"

void Object::Update(float deltaTime)
{
}

void Object::Render()
{
}

void Object::OnCollision(Collider& coll)
{
}

ObjectManager::~ObjectManager()
{
	for (auto& obj : objects)
		SAFE_DELETE(obj);

	for (auto& addObj : addObjects)
		SAFE_DELETE(addObj);
}


void ObjectManager::AddObject(Object* obj)
{
	addObjects.push_back(obj);
}

void ObjectManager::Collision()
{
	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		for (auto it2 = it + 1; it2 != objects.end(); ++it2)
		{
			if (!(*it)->bCollider || !(*it2)->bCollider) continue;

			for (auto body1 : (*it)->bodies)
			{
				for (auto body2 : (*it2)->bodies)
				{
					if (IntersectCollider(body1, body2))
					{
						(*it)->OnCollision(body2);
						(*it2)->OnCollision(body1);
					}
				}
			}
		}
	}
}

void ObjectManager::Update(float deltaTime)
{
	objects.insert(objects.end(), addObjects.begin(), addObjects.end());
	addObjects.clear();

	std::sort(objects.begin(), objects.end(), [](const Object* rhs, const Object* lhs) { return rhs->layer < lhs->layer; });

	for (auto it = objects.begin(); it != objects.end(); )
	{
		(*it)->Update(deltaTime);
		if ((*it)->destroy)
		{
			SAFE_DELETE((*it));
			it = objects.erase(it);
		}
		else
			++it;
	}
}

void ObjectManager::Render()
{
	for (auto& obj : objects)
		obj->Render();
}
