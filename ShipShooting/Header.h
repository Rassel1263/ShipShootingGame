#pragma once

#define SAFE_RELEASE(p) { if (p) { p->Release(); p = NULL; }}
#define SAFE_DELETE(p) { if (p) {delete p; p = NULL; } }
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <filesystem>
#include <functional>
#include <fstream>
#include <random>

#include "Singleton.h"
#include "Input.h"
#include "Time.h"

#include "Texture.h"
#include "Sprite.h"

#include "Camera.h"

#include "SoundManager.h"
#include "ShaderManager.h"
#include "ColorShader.h"

#include "Collider.h"
#include "Object.h"

#include "MiniMap.h"

#include "Scene.h"
extern Scene* nowScene;
#include "GameScene.h"
#include "GameScene2.h"
#include "MainScene.h"
#include "RankingScene.h"


#include "Game.h"