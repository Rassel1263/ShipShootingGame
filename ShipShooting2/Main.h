#pragma once
class Main : public Object
{
public:
	Sprite fadeSpr;

	int fadeIndex = 0;

	bool fade = false;
	std::vector<Sprite> ui;

	float alpha = 0.0f;

	int cNum = 0;
	int pNum = 0;

	Main();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void ChoiceBtn();
};

