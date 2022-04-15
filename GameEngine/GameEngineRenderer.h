#pragma once
#include "GameEngineActorSubObject.h"
#include "GameEngineEnum.h"
#include <map>

class GameEngineImage;	// 상하관계 불분명하기 때문에 참조 x
class GameEngineFolderImage;
class GameEngineRenderer : public GameEngineActorSubObject
{
	friend GameEngineActor;
	friend GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	inline void SetTransColor(unsigned int _Color)
	{
		TransColor_ = _Color;
	}

	// 그려질 위치
	inline void SetPivot(const float4 _Pos)
	{
		RenderPivot_ = _Pos;
	}

	// 렌더 시작점 타입 (CENTER or BOT))
	inline void SetPivotType(const RenderPivot& _Type)
	{
		PivotType_ = _Type;
	}

	// 그려질 때 크기 지정 타입
	inline void SetScaleMode(const RenderScaleMode& _Mode)
	{
		ScaleMode_ = _Mode;
	}

	// Image타입 이미지 - 크기 세팅
	void SetImageScale();

	// User타입 이미지 - 크기 세팅
	inline void SetScale(const float4& _Scale)
	{
		ScaleMode_ = RenderScaleMode::User;
		RenderScale_ = _Scale;
	}

	inline GameEngineImage* GetImage()
	{
		return Image_;
	}

	void SetImage(const std::string& _Name);

	void SetIndex(size_t _Index, float4 _Scale = { -1.0f, -1.0f });

	void CameraEffectOff()
	{
		IsCameraEffect_ = false;
	}

	void CameraEffectOn()
	{
		IsCameraEffect_ = true;
	}

	void SetOrder(int _Order) override;

protected:
	void Render();

private:
	friend class FrameAnimation;

	GameEngineImage* Image_;
	RenderPivot PivotType_;		// 이미지가 그려질 시작점
	RenderScaleMode ScaleMode_;	// ennum옵션 들고있는 용도
	float4 RenderPivot_;		// 사용자가 지정한 위치

	float4 RenderScale_;		// (사용자가 지정한) 화면에 그려질 크기 -> 확대, 축소 가능

	float4 RenderImageScale_;	// 이미지에서 잘라낼 크기
	float4 RenderImagePivot_;	// 이미지의 '어디까지' 잘라서 그릴지 

	unsigned int TransColor_;

	bool IsCameraEffect_;

///////////////////////////////////////////////////////////////// 애니메이션

private:
	class FrameAnimation : public GameEngineNameObject
	{
	public:
		GameEngineRenderer* Renderer_;
		GameEngineImage* Image_;
		GameEngineFolderImage* FolderImage_;

		int CurrentFrame_;
		int StartFrame_;
		int EndFrame_;
		float CurrentInterTime_;
		float InterTime_;
		bool Loop_;
		bool IsEnd;

	public:
		FrameAnimation()
			: Renderer_(nullptr)
			, Image_(nullptr)
			, CurrentFrame_(-1)
			, StartFrame_(-1)
			, EndFrame_(-1)
			, CurrentInterTime_(0.1f)
			, InterTime_(0.1f)
			, Loop_(true)
			, FolderImage_(nullptr)
			, IsEnd(false)

		{

		}

	public:
		void Update();

		void Reset()
		{
			CurrentFrame_ = StartFrame_;
			CurrentInterTime_ = InterTime_;
		}
	};

public:
	void CreateAnimation(const std::string& _Image, const std::string& _Name, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop = true);

	void CreateFolderAnimation(const std::string& _Image, const std::string& _Name, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop = true);

	// 만든 애니메이션을 실행
	void ChangeAnimation(const std::string& _Name);


	bool IsEndAnimation();

	bool IsAnimationName(const std::string& _Name);


private:
	std::map<std::string, FrameAnimation> Animations_;
	FrameAnimation* CurrentAnimation_;



};