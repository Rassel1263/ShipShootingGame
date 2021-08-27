#include "Header.h"
#include "Unit.h"

Unit::Unit()
{
	spr.LoadAll(L"a");
}

void Unit::Update(float deltaTime)
{
}

void Unit::Render()
{
	spr.Render(RenderInfo{});
}
