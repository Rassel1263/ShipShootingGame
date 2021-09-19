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

#include "Singleton.h"
#include "Input.h"
#include "Camera.h"

#include "Texture.h"
#include "Sprite.h"

#include "Collider.h"
#include "Object.h"

#include "Unit.h"
#include "Player.h"
#include "PlayerUI.h"

#include "CEnemy.h"
#include "FloatingEnemy.h"

#include "CBullet.h"

#include "Map.h"

#include "Scene.h"
extern Scene* nowScene;
#include "GameScene.h"

#include "Game.h"