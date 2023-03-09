#pragma once
#include "GameEnginePath.h"

class GameEngineFile : public GameEnginePath
{
public:
	// constrcuter destructer
	GameEngineFile();
	GameEngineFile(const std::string& _Path);
	GameEngineFile(std::filesystem::path _Path);
	// �ٸ� �����ڸ� ����鼭 �긦 ���� �����ڵ� �ʿ������� ������ ���� ����
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
