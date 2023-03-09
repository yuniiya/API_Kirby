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

	// ���ҽ� ��������
	ResourceLoad();

	// Default Kirby
	{
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
		GameEngineImage* KirbyLeft5 = GameEngineImageManager::GetInst()->Find("Default_Att_Left.bmp");
		KirbyLeft5->CutCount(10, 3);
		GameEngineImage* KirbyRight5 = GameEngineImageManager::GetInst()->Find("Default_Att_Right.bmp");
		KirbyRight5->CutCount(10, 3);
		GameEngineImage* KirbyLeft6 = GameEngineImageManager::GetInst()->Find("Default_Attack_Left.bmp");
		KirbyLeft6->CutCount(5, 1);
		GameEngineImage* KirbyRight6 = GameEngineImageManager::GetInst()->Find("Default_Attack_Right.bmp");
		KirbyRight6->CutCount(5, 1);
		GameEngineImage* KirbyLeft7 = GameEngineImageManager::GetInst()->Find("Default_Enter_Left.bmp");
		KirbyLeft7->CutCount(10, 4);
		GameEngineImage* KirbyRight7 = GameEngineImageManager::GetInst()->Find("Default_Enter_Right.bmp");
		KirbyRight7->CutCount(10, 4);
	}

	// Skilled Kirby
	{
		GameEngineImage* KirbyLeft1 = GameEngineImageManager::GetInst()->Find("Ice_Left.bmp");
		KirbyLeft1->CutCount(10, 11);
		GameEngineImage* KirbyRight1 = GameEngineImageManager::GetInst()->Find("Ice_Right.bmp");
		KirbyRight1->CutCount(10, 11);
		GameEngineImage* KirbyLeft2 = GameEngineImageManager::GetInst()->Find("Metal_Left.bmp");
		KirbyLeft2->CutCount(10, 7);
		GameEngineImage* KirbyRight2 = GameEngineImageManager::GetInst()->Find("Metal_Right.bmp");
		KirbyRight2->CutCount(10, 7);
		GameEngineImage* KirbyLeft3 = GameEngineImageManager::GetInst()->Find("Spark_Left.bmp");
		KirbyLeft3->CutCount(10, 14);
		GameEngineImage* KirbyRight3 = GameEngineImageManager::GetInst()->Find("Spark_Right.bmp");
		KirbyRight3->CutCount(10, 14);
		GameEngineImage* KirbyLeft4 = GameEngineImageManager::GetInst()->Find("Spark_Attack.bmp");
		KirbyLeft4->CutCount(5, 1);
	}

	// Effect
	{
		GameEngineImage* Effect1 = GameEngineImageManager::GetInst()->Find("Effect.bmp");
		Effect1->CutCount(10, 6);
		GameEngineImage* Effect2 = GameEngineImageManager::GetInst()->Find("Effect2.bmp");
		Effect2->CutCount(10, 6);
		GameEngineImage* Effect3 = GameEngineImageManager::GetInst()->Find("Effect_Transform.bmp");
		Effect3->CutCount(5, 1);
		GameEngineImage* EffectLeft2 = GameEngineImageManager::GetInst()->Find("Effect_Left.bmp");
		EffectLeft2->CutCount(10, 6);
		GameEngineImage* EffectRight2 = GameEngineImageManager::GetInst()->Find("Effect_Right.bmp");
		EffectRight2->CutCount(10, 6);
		GameEngineImage* Effect4 = GameEngineImageManager::GetInst()->Find("Effect_BossStar.bmp");
		Effect4->CutCount(10, 6);
		//GameEngineImage* Item1 = GameEngineImageManager::GetInst()->Find("Item1.bmp");
		//Item1->CutCount(1, 1);
		//GameEngineImage* Item2 = GameEngineImageManager::GetInst()->Find("Item2.bmp");
		//Item2->CutCount(1, 1);


		// Kirby
		{
			GameEngineImage* EffectLeft2 = GameEngineImageManager::GetInst()->Find("Effect_Slide_Left.bmp");
			EffectLeft2->CutCount(5, 2);
			GameEngineImage* EffectRight2 = GameEngineImageManager::GetInst()->Find("Effect_Slide_Right.bmp");
			EffectRight2->CutCount(5, 2);
			GameEngineImage* EffectLeft3 = GameEngineImageManager::GetInst()->Find("Effect_RunToStop_Left.bmp");
			EffectLeft3->CutCount(5, 1);
			GameEngineImage* EffectRight3 = GameEngineImageManager::GetInst()->Find("Effect_RunToStop_Right.bmp");
			EffectRight3->CutCount(5, 1);
			GameEngineImage* EffectLeft4 = GameEngineImageManager::GetInst()->Find("Effect_Ice_Left.bmp");
			EffectLeft4->CutCount(10, 2);
			GameEngineImage* EffectRight4 = GameEngineImageManager::GetInst()->Find("Effect_Ice_Right.bmp");
			EffectRight4->CutCount(10, 2);
			GameEngineImage* EffectLeft5 = GameEngineImageManager::GetInst()->Find("Effect_Inhale_Left.bmp");
			EffectLeft5->CutCount(5, 1);
			GameEngineImage* EffectRight5 = GameEngineImageManager::GetInst()->Find("Effect_Inhale_Right.bmp");
			EffectRight5->CutCount(5, 1);

		}

		// Monster
		{

		}

		// Boss
		{
			GameEngineImage* EffectBossLeft = GameEngineImageManager::GetInst()->Find("Effect_Boss_Left.bmp");
			EffectBossLeft->CutCount(10, 2);
			GameEngineImage* EffectBossRight = GameEngineImageManager::GetInst()->Find("Effect_Boss_Right.bmp");
			EffectBossRight->CutCount(10, 2);
		}
	
	}

	// Ű ����
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

		GameEngineInput::GetInst()->CreateKey("SkillRelease", VK_SHIFT);
	}

	// ���� 
	{
		GameEngineImage* WaddleDeeLeft = GameEngineImageManager::GetInst()->Find("WaddleDee_Left.bmp");
		WaddleDeeLeft->CutCount(5, 2);
		GameEngineImage* WaddleDeeRight = GameEngineImageManager::GetInst()->Find("WaddleDee_Right.bmp");
		WaddleDeeRight->CutCount(5, 2);
		GameEngineImage* BigWaddleLeft = GameEngineImageManager::GetInst()->Find("BigWaddleDee_Left.bmp");
		BigWaddleLeft->CutCount(5, 2);
		GameEngineImage* BigWaddleRight = GameEngineImageManager::GetInst()->Find("BigWaddleDee_Right.bmp");
		BigWaddleRight->CutCount(5, 2);
		//GameEngineImage* SnooterLeft = GameEngineImageManager::GetInst()->Find("Snooter_Left.bmp");
		//SnooterLeft->CutCount(5, 4);
		//GameEngineImage* SnooterRight = GameEngineImageManager::GetInst()->Find("Snooter_Right.bmp");
		//SnooterRight->CutCount(5, 4);
		GameEngineImage* ScarfyLeft = GameEngineImageManager::GetInst()->Find("Scarfy_Left.bmp");
		ScarfyLeft->CutCount(5, 1);
		GameEngineImage* ScarfyRight = GameEngineImageManager::GetInst()->Find("Scarfy_Right.bmp");
		ScarfyRight->CutCount(5, 1);
	}

	{
		GameEngineImage* PengyLeft = GameEngineImageManager::GetInst()->Find("Pengy_Left.bmp");
		PengyLeft->CutCount(5, 2);
		GameEngineImage* PengyRight = GameEngineImageManager::GetInst()->Find("Pengy_Right.bmp");
		PengyRight->CutCount(5, 2);

		GameEngineImage* SparkyLeft1 = GameEngineImageManager::GetInst()->Find("Sparky_Left.bmp");
		SparkyLeft1->CutCount(5, 2);
		GameEngineImage* SparkyRight1 = GameEngineImageManager::GetInst()->Find("Sparky_Right.bmp");
		SparkyRight1->CutCount(5, 2);

		GameEngineImage* SparkyLeft2 = GameEngineImageManager::GetInst()->Find("Sparky_Attack.bmp");
		SparkyLeft2->CutCount(5, 1);

		GameEngineImage* MetalunLeft = GameEngineImageManager::GetInst()->Find("Metalun_Left.bmp");
		MetalunLeft->CutCount(5, 5);
		GameEngineImage* MetalunRight = GameEngineImageManager::GetInst()->Find("Metalun_Right.bmp");
		MetalunRight->CutCount(5, 5);

		GameEngineImage* BossLeft = GameEngineImageManager::GetInst()->Find("Boss_Left.bmp");
		BossLeft->CutCount(5, 7);
		GameEngineImage* BossRight = GameEngineImageManager::GetInst()->Find("Boss_Right.bmp");
		BossRight->CutCount(5, 7);

		GameEngineImage* BossLeft1 = GameEngineImageManager::GetInst()->Find("King_Left.bmp");
		BossLeft1->CutCount(5, 7);
		GameEngineImage* BossRight1 = GameEngineImageManager::GetInst()->Find("King_Right.bmp");
		BossRight1->CutCount(5, 7);
		GameEngineImage* BossLeft2 = GameEngineImageManager::GetInst()->Find("King_Jump_Left.bmp");
		BossLeft2->CutCount(5, 7);
		GameEngineImage* BossRight2 = GameEngineImageManager::GetInst()->Find("King_Jump_Right.bmp");
		BossRight2->CutCount(5, 7);
		GameEngineImage* BossLeft3 = GameEngineImageManager::GetInst()->Find("King_Hammer_Left.bmp");
		BossLeft3->CutCount(5, 7);
		//GameEngineImage* BossRight3 = GameEngineImageManager::GetInst()->Find("King_Jump_Right.bmp");
		//BossRight3->CutCount(5, 7);
		GameEngineImage* BossLeft4 = GameEngineImageManager::GetInst()->Find("King_Jump_Hammer_Left.bmp");
		BossLeft4->CutCount(5, 7);
		//GameEngineImage* BossRight4 = GameEngineImageManager::GetInst()->Find("King_Jump_Right.bmp");
		//BossRight4->CutCount(5, 7);
	}

	{
		GameEngineImage* BossLeft1 = GameEngineImageManager::GetInst()->Find("Hammer_Left.bmp");
		BossLeft1->CutCount(5, 4);
		GameEngineImage* BossRight1 = GameEngineImageManager::GetInst()->Find("Hammer_Right.bmp");
		BossRight1->CutCount(5, 4);
		GameEngineImage* BossLeft2 = GameEngineImageManager::GetInst()->Find("Jump_Hammer_Left.bmp");
		BossLeft2->CutCount(5, 1);
		GameEngineImage* BossRight2 = GameEngineImageManager::GetInst()->Find("Jump_Hammer_Right.bmp");
		BossRight2->CutCount(5, 1);
	}


	// ���� ���� �� ���� ���� ����
	CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<Level_1>("Level_1");
	CreateLevel<Level_2>("Level_2");
	CreateLevel<Level_3>("Level_3");
	CreateLevel<Level_4>("Level_4");
	CreateLevel<BossRoomLevel>("BossRoomLevel");
	CreateLevel<BossLevel>("BossLevel");
	CreateLevel<EndingLevel>("EndingLevel");

	ChangeLevel("TitleLevel");
}

void Kirby::GameLoop()
{
}

void Kirby::GameEnd()
{
}

void Kirby::ResourceLoad()
{
	// �� �׶���
	{
		// ���� ���丮
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

	// �÷��̾� 
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

	{
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Actor");
		ResourcesDir.Move("Monster");

		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("bmp");
		AllImageFileList = ResourcesDir.GetAllFile("bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}
	}

	// ��������
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

	// BossLevel ���� �̹��� �ε�
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


	// ����
	{
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Sound");
		//ResourcesDir.Move("EffectSound");

		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile();

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineSound::LoadRes(AllImageFileList[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Sound");
		ResourcesDir.Move("EffectSound");

		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile();

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineSound::LoadRes(AllImageFileList[i].GetFullPath());
		}
	}

	// Effect
	{
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Actor");
		ResourcesDir.Move("Effect");

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
		ResourcesDir.Move("Actor");
		ResourcesDir.Move("Monster");
		ResourcesDir.Move("Boss");

		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("bmp");
		AllImageFileList = ResourcesDir.GetAllFile("bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}
	}


}
