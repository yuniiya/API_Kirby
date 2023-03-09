#pragma once
#include "GameEnginePath.h"

class GameEngineFile : public GameEnginePath
{
public:
	// constrcuter destructer
	GameEngineFile();
	GameEngineFile(const std::string& _Path);
	GameEngineFile(std::filesystem::path _Path);
	// 다른 생성자를 만들면서 얘를 만들어낼 생성자도 필요해졌기 때문에 따로 구현
	GameEngineFile(const GameEngineFile& _Other);
	~GameEngineFile();

	// delete Function
	//GameEngineFile(const GameEngineFile& _Other) = delete;
	//GameEngineFile(GameEngineFile&& _Other) noexcept = delete;
	GameEngineFile& operator=(const GameEngineFile& _Other) = delete;
	GameEngineFile& operator=(GameEngineFile&& _Other) noexcept = delete;

protected:

private:

};
