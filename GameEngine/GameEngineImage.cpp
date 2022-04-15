#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>

GameEngineImage::GameEngineImage()
	: ImageDC_(nullptr)
	, BitMap_(nullptr)
	, OldBitMap_(nullptr)
	, Info_{}
{

}

GameEngineImage::~GameEngineImage()
{
	if (nullptr != BitMap_)
	{
		DeleteObject(BitMap_);
		BitMap_ = nullptr;
	}

	if (nullptr != OldBitMap_)
	{
		DeleteObject(OldBitMap_);
		OldBitMap_ = nullptr;
	}

	if (nullptr != ImageDC_)
	{
		DeleteObject(ImageDC_);
		ImageDC_ = nullptr;
	}
}

// 내 구조로 처음에 만들어진 HDC를 편입시킨다
bool GameEngineImage::Create(HDC _DC)
{
	// 백 버퍼쪽 DC
	ImageDC_ = _DC;
	// 비트맵 정보 받아오기
	ImageScaleCheck();

	return true;
}

bool GameEngineImage::Load(const std::string& _Path)
{
	BitMap_ = static_cast<HBITMAP>(LoadImageA(
		nullptr,
		_Path.c_str(),
		IMAGE_BITMAP,
		0,
		0,
		LR_LOADFROMFILE
		));

	if (nullptr == BitMap_)
	{
		MsgBoxAssertString(_Path + "이미지 로드에 실패했습니다. 여러분들이 살펴봐야할 문제 1. 경로는 제대로 됐나요? 2. 디버깅은 제대로 봤나요");
	}

	// DC를 비운다
	ImageDC_ = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC_)
	{
		MsgBoxAssert("ImageDc 생성에 실패했습니다.");
	}

	OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

	ImageScaleCheck();

	return true;
}

// 백 버퍼 만들 용도
bool GameEngineImage::Create(float4 _Scale)
{
	// 0,0 이미지를 만들려고 하는지 체크 
	if (true == _Scale.IsZero2D())
	{
		MsgBoxAssert("크기가 0인 이미지를 제작하려고 했습니다");
		return false;
	}

	// 이미지 크기와 동일한 비트맵을 만든다
	BitMap_ = CreateCompatibleBitmap(GameEngineWindow::GetHDC(), _Scale.ix(), _Scale.iy());
	// DC생성 후 디폴트 비트맵과 연결을 끊는다
	ImageDC_ = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC_)
	{
		MsgBoxAssert("ImageDC 생성에 실패했습니다");
	}

	// 만들어둔 비트맵과 DC를 연결한다 
	OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

	// 완성된 비트맵의 정보를 얻어온다
	ImageScaleCheck();

	return true;
}


void GameEngineImage::ImageScaleCheck()
{
	// DC와 연결된 비트맵의 핸들 얻어오기
	HBITMAP CurrentBitMap = (HBITMAP)GetCurrentObject(ImageDC_, OBJ_BITMAP);
	GetObject(CurrentBitMap, sizeof(BITMAP), &Info_);
}


void GameEngineImage::BitCopy(GameEngineImage* _Other)
{
	// 0,0에서 출력, 시작점, 크기만큼
	BitCopy(_Other, { 0, 0 }, _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos)
{
	// 출력할 위치 받아서 출력, 시작점, 크기만큼 
	BitCopy(_Other, _CopyPos, _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopyCenter(GameEngineImage* _Other, const float4& _CopyPos)
{
	// 이미지를 출력할 위치 - (크기/2) = 중앙
	BitCopy(_Other, _CopyPos - _Other->GetScale().Half(), _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopyCenterPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot)
{
	// 중앙에서 CopyPivot만큼 위로 올려서 출력
	BitCopy(_Other, _CopyPos - _Other->GetScale().Half() + _CopyPivot, _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopyBot(GameEngineImage* _Other, const float4& _CopyPos)
{
	float4 ImagePivot = _Other->GetScale().Half();
	ImagePivot.y = _Other->GetScale().y;

	// 출력할 위치 - y
	BitCopy(_Other, _CopyPos - ImagePivot, _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopyBotPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot)
{
	float4 ImagePivot = _Other->GetScale().Half();
	ImagePivot.y = _Other->GetScale().y;

	// 출력할 위치 - y 에서 CopyPivot만큼 위로 올려서 출력 
	BitCopy(_Other, _CopyPos - ImagePivot + _CopyPivot, float4{ 0, 0 }, _Other->GetScale());
}

void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyScale, const float4& _OtherPivot)
{	
	// 백 버퍼 이미지 -> 메인 윈도우로 복사
	BitBlt(
		ImageDC_,			// 이미지를 출력할 위치의 핸들
		_CopyPos.ix(),		// 이미지를 출력할 위치
		_CopyPos.iy(),
		_CopyScale.ix(),	// 출력할 이미지의 크기 (A)
		_CopyScale.iy(),
		_Other->ImageDC_,	// 복사될 이미지의 핸들
		_OtherPivot.ix(),	// 가져올 이미지의 시작점 (여기서 A만큼 잘라와서 그린다)
		_OtherPivot.iy(),
		SRCCOPY
	);
}

// =================================================================

// 사용자가 넣어준 크기로 그린다
//void GameEngineImage::TransCopyCenterScale(GameEngineImage* _Other, const float4& _CopyPos, const float4& _RenderScale, unsigned int _TransColor)
//{
//	TransCopy(_Other, _CopyPos - _RenderScale.Half(), _RenderScale, float4{ 0,0 }, _Other->GetScale(), _TransColor);
//}
//
//// 이미지의 크기로 그린다
//void GameEngineImage::TransCopyCenter(GameEngineImage* _Other, const float4& _CopyPos, unsigned int _TransColor)
//{
//	TransCopy(_Other, _CopyPos - _Other->GetScale().Half(), _Other->GetScale(), float4{ 0, 0 }, _Other->GetScale(), _TransColor);
//}

void GameEngineImage::TransCopy(GameEngineImage* _Other, const float4& _CopyPos,
	const float4& _CopyScale, 
	const float4& _OtherPivot, const float4& _OtherScale, unsigned int _TransColor)
{
	TransparentBlt(
		ImageDC_,			// 이미지를 출력할 위치의 핸들
		_CopyPos.ix(),		// 이미지를 출력할 시작 위치 
		_CopyPos.iy(),
		_CopyScale.ix(),	// 출력할 이미지의 크기 지정
		_CopyScale.iy(),
		_Other->ImageDC_,	// 복사될 이미지의 핸들
		_OtherPivot.ix(),	// 가져올 이미지의 시작점 (여기서 A만큼 잘라와서 그린다)
		_OtherPivot.iy(),
		_OtherScale.ix(),	// 잘라낼 크기 (A) -> 지정한 CopyScale에 맞춰 A를 늘리거나 줄인다
		_OtherScale.iy(),
		_TransColor			// 해당 색상은 제외하고 출력
	);
}

void GameEngineImage::CutCount(int _x, int _y)
{
	float4 Scale = { GetScale().x / _x, GetScale().y / _y };
	Cut(Scale);
}

void GameEngineImage::Cut(const float4& _CutSize)
{
	/*if (0 != (GetScale().ix() % _CutSize.ix()))
	{
		MsgBoxAssert("자를 수 있는 수치가 딱 맞아떨어지지 않습니다.");
	}

	if (0 != (GetScale().iy() % _CutSize.iy()))
	{
		MsgBoxAssert("자를 수 있는 수치가 딱 맞아떨어지지 않습니다.");
	}*/

	// Sprite상 이미지의 가로, 세로 개수
	int XCount = GetScale().ix() / _CutSize.ix();
	int YCount = GetScale().iy() / _CutSize.iy();

	// 가로, 세로 개수 만큼
	for (int y = 0; y < YCount; y++)
	{
		for (int x = 0; x < XCount; x++)
		{
			CutPivot_.push_back({ static_cast<float>(x * _CutSize.ix()), static_cast<float>(y * _CutSize.iy()) });
			CutScale_.push_back(_CutSize);
		}
	}
}

int GameEngineImage::GetImagePixel(int _x, int _y)
{
	// 화면 밖으로 나가면 해당 부분 검은색으로 인식 -> 따라서 플레이어가 화면 밖으로 못 나간다 
	if (0 > _x)
	{
		return RGB(0, 0, 0);
	}

	if (0 > _y)
	{
		return RGB(0, 0, 0);
	}

	if (GetScale().ix() <= _x)
	{
		return RGB(0, 0, 0);
	}

	if (GetScale().iy() <= _y)
	{
		return RGB(0, 0, 0);
	}

	return GetPixel(ImageDC_, _x, _y);
}
