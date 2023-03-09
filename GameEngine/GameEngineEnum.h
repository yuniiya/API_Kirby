#pragma once

// 이미지가 그려질 때 시작점 
enum class RenderPivot
{
	CENTER,
	BOT,
};

// 이미지 불러올 때 크기 타입 
enum class RenderScaleMode
{
	Image,		// 원본 그대로 
	User,		// 사용자 지정
};

enum class CollisionType
{
	Point,
	Circle,
	Rect,
	Max		// 나올 수 있는 최대 경우의 수
};

enum class EngineMax
{
	RENDERORDERMAX = 2147483647,
};