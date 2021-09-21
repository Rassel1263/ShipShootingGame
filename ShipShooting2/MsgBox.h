#pragma once
class MsgBox : public ObjectUI
{
public:
	Sprite spr;
	Sprite msgBox;

	bool spawnMsg = false;
	bool closeMsg = false;
	float msgTime = 0.0f;
	float destColor = 1.0f;

	MsgBox();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void SpawnMsgBox(std::wstring message);
};

