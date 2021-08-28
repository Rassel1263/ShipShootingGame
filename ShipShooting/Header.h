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

#include "Header.h"

#include "Singleton.h"
#include "Input.h"

#include "Texture.h"
#include "Sprite.h"

#include "Camera.h"

#include "Collider.h"
#include "Object.h"

#include "Scene.h"
extern Scene* nowScene;
#include "GameScene.h"


#include "Game.h"