#pragma once
class ShaderManager : public Singleton<ShaderManager>
{
private:
	std::map<std::string, LPD3DXEFFECT> effects;

public:
	~ShaderManager();

	HRESULT CreateEffect(std::string name, LPCWSTR fileName, DWORD flag);
	LPD3DXEFFECT& GetEffect(std::string name);
};

