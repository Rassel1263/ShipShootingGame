#pragma once

#define IntEnum(p) static_cast<int>(p)

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <map>
#include <filesystem>
#include <thread>
#include <mutex>
#include <functional>
#include <algorithm>
#include <cwctype>
#include <random>

#include "Singleton.h"
#include "Input.h"
#include "Camera.h"

#include "Texture.h"
#include "Sprite.h"

#include "ShaderManager.h"
#include "ColorShader.h"

#include "Collider.h"
#include "Object.h"

#include "CWeapon.h"

#include "Unit.h"

#include "CEnemy.h"
#include "FloatingEnemy.h"
#include "FlyingEnemy.h"
#include "EnemyManager.h"

#include "Player.h"
#include "PlayerUI.h"
#include "MsgBox.h"

#include "CBullet.h"
#include "MachinegunBullet.h"
#include "HomingBullet.h"

#include "Obstacle.h"
#include "ObstacleManager.h"
#include "Cloud.h"

#include "Item.h"
#include "ItemUI.h"

#include "Font.h"
#include "Effect.h"
#include "StageFont.h"
#include "FocusedFire.h"
#include "Airsupport.h"

#include "MiniMap.h"
#include "Map.h"

#include "Scene.h"
extern Scene* nowScene;
#include "GameScene.h"

#include "Game.h"