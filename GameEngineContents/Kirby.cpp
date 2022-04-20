#include "Kirby.h"
#include "TitleLevel.h"
#include "Level_1.h"
#include "Level_2.h"
#include "Level_3.h"
#include "Level_4.h"
#include "BossRoomLevel.h"
#include "BossLevel.h"
#include "EndingLevel.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineSound.h>


Kirby::Kirby()
{

}
Kirby::~Kirby()
{

}

void Kirby::GameInit()
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({0, 0}, { 1024, 768 });	// 4:3

	// 리소스 가져오기
	ResourceLoad();

	GameEngineImage* KirbyLeft1 = GameEngineImageManager::GetInst()->Find("Default_Left.bmp");
	KirbyLeft1->CutCount(10, 14);
	GameEngineImage* KirbyRight1 = GameEngineImageManager::GetInst()->Find("Default_Right.bmp");
	KirbyRight1->CutCount(10, 14);
	GameEngineImage* KirbyLeft2 = GameEngineImageManager::GetInst()->Find("Default_Jump_Left.bmp");
	KirbyLeft2->CutCount(10, 1);
	GameEngineImage* KirbyRight2 = GameEngineImageManager::GetInst()->Find("Default_Jump_Right.bmp");
	KirbyRight2->CutCount(10, 1);
	GameEngineImage* KirbyLeft3 = GameEngineImageManager::GetInst()->Find("Default_Float_Left.bmp");
	KirbyLeft3->CutCount(10, 2);
	GameEngineImage* KirbyRight3 = GameEngineImageManager::GetInst()->Find("Default_Float_Right.bmp");
	KirbyRight3->CutCount(10, 2);
	GameEngineImage* KirbyLeft4 = GameEngineImageManager::GetInst()->Find("Default_Fall_Left.bmp");
	KirbyLeft4->CutCount(10, 2);
	GameEngineImage* KirbyRight4 = GameEngineImageManager::GetInst()->Find("Default_Fall_Right.bmp");
	KirbyRight4->CutCount(10, 2);


	// 키 생성
	if (false == GameEngineInput::GetInst()->IsKey("TitleLevel"))
	{
		GameEngineInput::GetInst()->CreateKey("TitleLevel", 'P');
		GameEngineInput::GetInst()->CreateKey("Level_1", '1');
		GameEngineInput::GetInst()->CreateKey("Level_2", '2');
		GameEngineInput::GetInst()->CreateKey("Level_3", '3');
		GameEngineInput::GetInst()->CreateKey("Level_4", '4');
		GameEngineInput::GetInst()->CreateKey("BossRoomLevel", '5');
		GameEngineInput::GetInst()->CreateKey("BossLevel", '6');
		GameEngineInput::GetInst()->CreateKey("EndingLevel", '7');

		GameEngineInput::GetInst()->CreateKey("NextLevel", VK_SPACE);

		GameEngineInput::GetInst()->CreateKey("DebugMode", 'O');
	}


	// 레벨 생성 및 현재 레벨 설정
	CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<Level_1>("Level_1");
	CreateLevel<Level_2>("Level_2");
	CreateLevel<Level_3>("Level_3");
	CreateLevel<Level_4>("Level_4");
	CreateLevel<BossRoomLevel>("BossRoomLevel");
	CreateLevel<BossLevel>("BossLevel");
	CreateLevel<EndingLevel>("EndingLevel");

	ChangeLevel("Level_1");
}

void Kirby::GameLoop()
{
}

void Kirby::GameEnd()
{
}

void Kirby::ResourceLoad()
{
	// 백 그라운드
	{
		// 현재 디렉토리
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Level");

		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}
	}

	// 커비 (Test용)
	//{
	//	GameEngineDirectory ResourcesDir;
	//	ResourcesDir.MoveParent("API");
	//	ResourcesDir.Move("Resources");
	//	ResourcesDir.Move("Player");

	//	std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("bmp");
	//	AllImageFileList = ResourcesDir.GetAllFile("bmp");

	//	for (size_t i = 0; i < AllImageFileList.size(); i++)
	//	{
	//		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	//	}
	//}

	{
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Actor");
		ResourcesDir.Move("Kirby");

		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("bmp");
		AllImageFileList = ResourcesDir.GetAllFile("bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}
	}

	// 스테이지
	{
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Actor");
		ResourcesDir.Move("Stage");

		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("bmp");
		AllImageFileList = ResourcesDir.GetAllFile("bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("UI");

		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("bmp");
		AllImageFileList = ResourcesDir.GetAllFile("bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}
	}

	// BossLevel 폴더 이미지 로드
	{
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Level");

		std::vector<GameEngineFile> PlayerImageFolderList = ResourcesDir.GetAllFolder();
		for (size_t i = 0; i < PlayerImageFolderList.size(); ++i)
		{
			GameEngineImageManager::GetInst()->FolderImageLoad(PlayerImageFolderList[i].GetFullPath());
		}
	}


	// 사운드
	{
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Sound");
		//ResourcesDir.Move("Effect");

		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile();

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineSound::LoadRes(AllImageFileList[i].GetFullPath());
		}
	}

}
