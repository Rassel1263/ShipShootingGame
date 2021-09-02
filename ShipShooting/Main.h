#pragma once
class Main : public Object
{
public:
	Sprite bck;
	std::vector<Sprite> button;

	int cNum = 0;
	Main();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

