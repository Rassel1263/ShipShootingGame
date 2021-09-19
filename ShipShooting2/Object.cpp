#include "DXUT.h"
#include "Object.h"

void Object::CreateCollider(D3DXVECTOR2 min, D3DXVECTOR2 max, std::wstring tag, D3DXCOLOR color)
{
	Collider::AABB aabb = { min, max };
	bodies.push_back(Collider(this, tag, &aabb, color));
}

void Object::Update(float deltaTime)
{
}

void Object::Render()
{
#ifdef _DEBUG
	if (bCollider)
	{
		for (auto body : bodies)
		{
			D3DXMATRIX matrix;

			if (bCamera)
				D3DXMatrixTranslation(&matrix, pos.x, pos.y, 0.0f);
			else
				D3DXMatrixTranslation(&matrix, pos.x + Camera::GetInstance().cameraPos.x, pos.y + Camera::GetInstance().cameraPos.y, 0.0f);

			if (body.type == Collider::Type::AABB)
			{
				Game::GetInstance().DrawLine(body.aabb.min, D3DXVECTOR2(body.aabb.max.x, body.aabb.min.y), matrix, body.color);
				Game::GetInstance().DrawLine(D3DXVECTOR2(body.aabb.max.x, body.aabb.min.y), body.aabb.max, matrix, body.color);
				Game::GetInstance().DrawLine(body.aabb.max, D3DXVECTOR2(body.aabb.min.x, body.aabb.max.y), matrix, body.color);
				Game::GetInstance().DrawLine(D3DXVECTOR2(body.aabb.min.x, body.aabb.max.y), body.aabb.min, matrix, body.color);
			}
		}
	}
#endif
}

void Object::OnCollision(Collider& coli)
{
}

void ObjectUI::Update(float deltaTime)
{
}

void ObjectUI::Render()
{
}

void ObjectUI::OnCollision(Collider& coli)
{
}

ObjectManager::~ObjectManager()
{
	for (auto& obj : objects)
		SAFE_DELETE(obj);

	for (auto& obj : uiObjects)
		SAFE_DELETE(obj);

	for (auto& addObj : addObjects)
		SAFE_DELETE(addObj);

	for (auto& addObj : addUIObjects)
		SAFE_DELETE(addObj);
}

void ObjectManager::AddObject(Object* obj)
{
	addObjects.push_back(obj);
}

void ObjectManager::AddObject(ObjectUI* obj)
{
	addUIObjects.push_back(obj);
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

	uiObjects.insert(uiObjects.end(), addUIObjects.begin(), addUIObjects.end());
	addUIObjects.clear();

	std::sort(objects.begin(), objects.end(), [](const Object* lhs, const Object* rhs) { return lhs->layer < rhs->layer; });
	std::sort(uiObjects.begin(), uiObjects.end(), [](const ObjectUI* lhs, const ObjectUI* rhs) {return lhs->layer < rhs->layer; });

	for (auto& obj : objects)
		obj->Update(deltaTime);

	for (auto& obj : uiObjects)
		obj->Update(deltaTime);

	for (auto it = objects.begin(); it != objects.end();)
	{
		if ((*it)->destroy)
		{
			delete* it;
			it = objects.erase(it);
		}
		else
			++it;
	}

	for (auto it = uiObjects.begin(); it != uiObjects.end();)
	{
		if ((*it)->destroy)
		{
			delete* it;
			it = uiObjects.erase(it);
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

void ObjectManager::UIRender()
{
	for (auto& obj : uiObjects)
		obj->Render();
}
