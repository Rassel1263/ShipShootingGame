#pragma once
class MachinegunBullet : public CBullet
{
public:
	MachinegunBullet(D3DXVECTOR2 pos, Unit* target, std::wstring tag, float damage, float speed);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void CreateEffect() override;

};

