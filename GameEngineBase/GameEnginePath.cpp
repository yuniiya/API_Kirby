#include "GameEnginePath.h"

GameEnginePath::GameEnginePath()
{

}
GameEnginePath::GameEnginePath(const std::filesystem::path& _Path)
    : Path_(_Path)
{
}
GameEnginePath::~GameEnginePath()
{

}

void GameEnginePath::SetCurrentPath()
{
    // 현재 폴더
    Path_ = std::filesystem::current_path();
}

// 유효한 경로인지 확인
bool GameEnginePath::IsExits()
{   
    return std::filesystem::exists(Path_);
}

// 확장자
std::string GameEnginePath::GetExtension()
{
    return Path_.extension().string();
}

std::string GameEnginePath::GetFileName()
{
    return Path_.filename().string();
}

std::string GameEnginePath::GetFullPath()
{
    return Path_.string();
}
