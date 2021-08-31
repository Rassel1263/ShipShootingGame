#include "Header.h"
#include "Object.h"

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

			if (body.type == Collider::TYPE::AABB)
			{
				Game::GetInstance().DrawLine(body.aabb.min, D3DXVECTOR2(body.aabb.max.x, body.aabb.min.y), matrix, body.color);
				Game::GetInstance().DrawLine(D3DXVECTOR2(body.aabb.max.x, body.aabb.min.y), body.aabb.max, matrix, body.color);
				Game::GetInstance().DrawLine(body.aabb.max, D3DXVECTOR2(body.aabb.min.x, body.aabb.max.y), matrix, body.color);
				Game::GetInstance().DrawLine(D3DXVECTOR2(body.aabb.min.x, body.aabb.max.y), body.aabb.min, matrix, body.color);
			}
			else if (body.type == Collider::TYPE::Circle)
			{
				D3DXVECTOR2 position[36];
				for (int i = 0; i < 36; ++i)
					position[i] = D3DXVec2Rotation(D3DXVECTOR2(0.0f, body.circle.radius), i * 10.0f);
				for (int i = 0; i < 36; ++i)
					if (bCamera)
						Game::GetInstance().DrawLine(position[i], position[(i + 1) % 36], matrix, body.color);
			}
		}
	}
#endif
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
