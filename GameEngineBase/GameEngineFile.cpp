#include "GameEngineFile.h"

GameEngineFile::GameEngineFile()
{

}

// 파일 or 문자 뭐가 들어오건 경로는 받은걸로 세팅
GameEngineFile::GameEngineFile(const std::string& _Path)
{
	Path_ = _Path;
}
GameEngineFile::GameEngineFile(std::filesystem::path _Path)
{
	Path_ = _Path;
}
GameEngineFile::GameEngineFile(const GameEngineFile& _Other)
{
	Path_ = _Other.Path_;
}
GameEngineFile::~GameEngineFile()
{

}


