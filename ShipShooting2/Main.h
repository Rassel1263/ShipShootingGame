#pragma once
class Main : public Object
{
public:
	Sprite fadeSpr;

	bool fade = false;
	std::vector<Sprite> ui;

	int cNum = 0;
	int pNum = 0;

	Main();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void ChoiceBtn();
};

