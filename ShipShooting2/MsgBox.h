#pragma once
class MsgBox : public ObjectUI
{
public:
	Sprite spr[2];
	Sprite msgBox[2];

	struct MsgInfo
	{
		bool spawnMsg = false;
		bool closeMsg = false;
		float msgTime = 0.0f;
		float destColor = 1.0f;
	} msgInfo[2];


	MsgBox();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void SpawnMsgBox(std::wstring message);
	void SpawnMsgBox2(std::wstring message);

	void MessageUpdate(float deltaTime, int i);
};

