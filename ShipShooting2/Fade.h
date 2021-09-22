#pragma once
class Fade : public ObjectUI
{
public:
	Sprite spr;
	std::function<void()> func;

	Fade(std::function<void()> func);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

