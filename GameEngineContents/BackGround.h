#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineImage;
class GameEngineRenderer;
// class FrameAnimation;
class BackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	BackGround();
	~BackGround();

	// delete Function
	BackGround(const BackGround& _Other) = delete;
	BackGround(BackGround&& _Other) noexcept = delete;
	BackGround& operator=(const BackGround& _Other) = delete;
	BackGround& operator=(BackGround&& _Other) noexcept = delete;

	// �� �׶��� �ʿ��� ������ ���
	GameEngineRenderer* GetRenderer()
	{
		return Image_;
	}

	/*FrameAnimation* GetAnimationRenderer()
	{
		return Animation_;
	}*/


protected:

private:
	void Start() override;
	void Render() override;

private:
	GameEngineRenderer* Image_;

};
