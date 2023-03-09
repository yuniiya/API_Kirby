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
    // ���� ����
    Path_ = std::filesystem::current_path();
}

// ��ȿ�� ������� Ȯ��
bool GameEnginePath::IsExits()
{   
    return std::filesystem::exists(Path_);
}

// Ȯ����
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
