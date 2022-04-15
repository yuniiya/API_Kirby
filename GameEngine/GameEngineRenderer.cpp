#include "GameEngineRenderer.h"
#include "GameEngineImageManager.h"
#include "GameEngine.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineLevel.h>

#pragma comment(lib, "msimg32.lib")

GameEngineRenderer::GameEngineRenderer()
	: Image_(nullptr)
	, PivotType_(RenderPivot::CENTER)
	, ScaleMode_(RenderScaleMode::Image)	// 기본 크기는 원본
	, TransColor_(RGB(255, 0, 255))			// 마젠타
	, RenderImagePivot_({0,0})
	, RenderImageScale_({0,0})
	, CurrentAnimation_(nullptr)
	, IsCameraEffect_(true)			// 기본은 true로 해놓고 UI처럼 카메라 영향 안 받는 애들은 따로 지정
{

}
GameEngineRenderer::~GameEngineRenderer()
{

}

void GameEngineRenderer::SetImageScale()
{
	if (nullptr == Image_)
	{
		MsgBoxAssert("존재하지 않는 이미지로 크기를 조절하려 했습니다");
		return;
	}

	// 이미지 크기 그대로 세팅
	ScaleMode_ = RenderScaleMode::Image;

	RenderScale_ = Image_->GetScale();
	RenderImageScale_ = Image_->GetScale();
}

void GameEngineRenderer::SetImage(const std::string& _Name)
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find(_Name);
	if (nullptr == FindImage)
	{
		MsgBoxAssertString(_Name + "존재하지 않는 이미지를 세팅하려 했습니다");
	}

	Image_ = FindImage;
	SetImageScale();
}

// Renderer는 이미지가 세팅되어있어야 실행 가능 -> 세팅된 이미지 렌더
void GameEngineRenderer::Render()
{
	// 애니메이션이 들어왔다면 이미지는 애니메이션으로 실행
	if (nullptr != CurrentAnimation_)
	{
		CurrentAnimation_->Update();
	}

	if (nullptr == Image_)
	{
		MsgBoxAssert("렌더러에 이미지가 세팅되어 있지 않으면 렌더링이 안됩니다.");
		return;
	}

	// 수정된 위치
	float4 RenderPos = GetActor()->GetPosition() + RenderPivot_;

	// 카메라에 영향받는 엑터라면 이동좌표와 반대로 
	if (true == IsCameraEffect_)
	{
		RenderPos -= GetActor()->GetLevel()->GetCameraPos();
	}

	switch (PivotType_)
	{
	case RenderPivot::CENTER:
		GameEngine::BackBufferImage()->TransCopy(Image_, RenderPos - RenderScale_.Half(), RenderScale_, RenderImagePivot_, RenderImageScale_, TransColor_);
		break;
	case RenderPivot::BOT:
	{
		// 센터에서
		float4 Scale = RenderScale_.Half();
		// 세로 중심점을 내린다 
		Scale.y *= 2.0f;

		GameEngine::BackBufferImage()->TransCopy(Image_, RenderPos - Scale, RenderScale_, RenderImagePivot_, RenderImageScale_, TransColor_);
		break;
	}	
	default:
		break;
	}
}

void GameEngineRenderer::SetIndex(size_t _Index, const float4 _Scale)
{
	// 잘려져 있는 이미지만 들어올 수 있게
	if (false == Image_->IsCut())
	{
		MsgBoxAssert("이미지를 부분적으로 사용할수 있게 잘려지있지 않은 이미지 입니다.");
		return;
	}

	// 크기를 따로 지정했다면
	if (_Scale.x <= 0 || _Scale.y <= 0)
	{
		// 얼마나 잘라와서 화면에 그릴지 
		RenderScale_ = Image_->GetCutScale(_Index);
	}
	else
	{
		RenderScale_ = _Scale;
	}

	// 어디부터 얼마나 자를지
	RenderImagePivot_ = Image_->GetCutPivot(_Index);
	RenderImageScale_ = Image_->GetCutScale(_Index);

}

/////////////////////////////////////// 애니메이션

void GameEngineRenderer::CreateFolderAnimation(const std::string& _Image, const std::string& _Name, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop /*= true*/)
{
	GameEngineFolderImage* FindImage = GameEngineImageManager::GetInst()->FolderImageFind(_Image);
	if (nullptr == FindImage)
	{
		MsgBoxAssertString(_Name + "존재하지 않는 이미지로 애니메이션을 만들려고 했습니다.");
		return;
	}

	if (Animations_.end() != Animations_.find(_Name))
	{
		MsgBoxAssert("이미 존재하는 애니메이션을 또 만들려고 했습니다.");
		return;
	}

	FrameAnimation& NewAnimation = Animations_[_Name];

	NewAnimation.SetName(_Name);
	NewAnimation.Renderer_ = this;
	NewAnimation.FolderImage_ = FindImage;
	NewAnimation.CurrentFrame_ = _StartIndex;
	NewAnimation.StartFrame_ = _StartIndex;
	NewAnimation.EndFrame_ = _EndIndex;
	NewAnimation.CurrentInterTime_ = _InterTime;
	NewAnimation.InterTime_ = _InterTime;
	NewAnimation.Loop_ = _Loop;

}



void GameEngineRenderer::ChangeAnimation(const std::string& _Name)
{
	std::map<std::string, FrameAnimation>::iterator FindIter = Animations_.find(_Name);

	if (Animations_.end() == FindIter)
	{
		MsgBoxAssert("존재하지 않는 애니메이션으로 체인지 하려고 했습니다.");
		return;
	}

	CurrentAnimation_ = &FindIter->second;
}


void GameEngineRenderer::CreateAnimation(
	const std::string& _Image,
	const std::string& _Name,
	int _StartIndex,
	int _EndIndex,
	float _InterTime,
	bool _Loop /*= true*/)
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find(_Image);

	if (nullptr == FindImage)
	{
		MsgBoxAssert("존재하지 않는 이미지로 애니메이션을 만들려고 했습니다.");
		return;
	}

	if (Animations_.end() != Animations_.find(_Name))
	{
		MsgBoxAssert("이미 존재하는 애니메이션을 또 만들려고 했습니다..");
		return;
	}

	//FrameAnimation Animation;
	//Animation.insert(std::make_pair(, FrameAnimation()));
	
	// 여기까지 왔다면 애니메이션이 무조건 있다는 뜻이기 때문에 find와 insert동시에 처리해서 바로 만든다
	FrameAnimation& NewAnimation = Animations_[_Name];
	NewAnimation.Renderer_ = this;
	NewAnimation.Image_ = FindImage;
	NewAnimation.CurrentFrame_ = _StartIndex;
	NewAnimation.StartFrame_ = _StartIndex;
	NewAnimation.EndFrame_ = _EndIndex;
	NewAnimation.CurrentInterTime_ = _InterTime;
	NewAnimation.InterTime_ = _InterTime;
	NewAnimation.Loop_ = _Loop;


}

void GameEngineRenderer::FrameAnimation::Update()
{
	// End 초기값
	IsEnd = false;
	CurrentInterTime_ -= GameEngineTime::GetInst()->GetDeltaTime();
	if (0 >= CurrentInterTime_)
	{
		CurrentInterTime_ = InterTime_;
		++CurrentFrame_;

		if (EndFrame_ < CurrentFrame_)
		{
			if (true == Loop_)
			{
				IsEnd = true;
				CurrentFrame_ = StartFrame_;	// Loop가 True라면 이미지를 반복시킨다.
			}
			else
			{
				IsEnd = true;
				CurrentFrame_ = EndFrame_;		// Loop가 false라면 애니메이션 진행후 EndFrame으로 고정시킨다.
			}
		}
	}

	if (nullptr != Image_)
	{
		Renderer_->Image_ = Image_;		// 렌더러에게 이 애니메이션 만들때 세팅했떤 이미지를 세팅해준다.
		Renderer_->SetIndex(CurrentFrame_);	// 렌더러에게 인덱스도 세팅해준다. 즉, 해당 애니메이션 이미지의 몇번째 칸(Index) 세팅해주면 렌더러는 알아서 출력한다.
	}
	else if (nullptr != FolderImage_)
	{
		Renderer_->Image_ = FolderImage_->GetImage(CurrentFrame_);		// 렌더러에게 이 애니메이션 만들때 세팅했떤 이미지를 세팅해준다.
		Renderer_->SetImageScale();	// 렌더러에게 인덱스도 세팅해준다. 즉, 해당 애니메이션 이미지의 몇번째 칸(Index) 세팅해주면 렌더러는 알아서 출력한다.
	}
}

// 레벨에서 관리하는 AllRender에 Order를 제거+추가하는 기능까지 추가
void GameEngineRenderer::SetOrder(int _Order)
{
	if (nullptr == GetActor())
	{
		MsgBoxAssert("액터가 세팅되지 않습니다.");
	}

	if (nullptr == GetActor()->GetLevel())
	{
		MsgBoxAssert("레벨이 세팅되지 않았습니다.");
	}

	if (_Order == GetOrder())
	{
		return;
	}

	GetActor()->GetLevel()->ChangeRenderOrder(this, _Order);
}

bool GameEngineRenderer::IsEndAnimation()
{
	return CurrentAnimation_->IsEnd;
}

bool GameEngineRenderer::IsAnimationName(const std::string& _Name)
{
	return CurrentAnimation_->GetNameConstRef() == _Name;
}