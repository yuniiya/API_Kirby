#pragma once
#include <math.h>

class GameEngineMath
{
public:
	static const float PIE;
	static const float DEG;
	static const float DegreeToRadian;

public:
	// constrcuter destructer
	GameEngineMath();
	~GameEngineMath();

	// delete Function
	GameEngineMath(const GameEngineMath& _Other) = delete;
	GameEngineMath(GameEngineMath&& _Other) noexcept = delete;
	GameEngineMath& operator=(const GameEngineMath& _Other) = delete;
	GameEngineMath& operator=(GameEngineMath&& _Other) noexcept = delete;

protected:

private:

};

// float을 형변환하는 클래스 
class float4
{
public:
	static float4 DegreeToDirectionFloat4(float _Degree)
	{
		return RadianToDirectionFloat4(_Degree * GameEngineMath::DegreeToRadian);
	}

	static float4 RadianToDirectionFloat4(float _Radian)
	{
		return { cosf(_Radian), sinf(_Radian) };
	}

public:
	static float4 LEFT;
	static float4 RIGHT;
	static float4 UP;
	static float4 DOWN;
	static float4 ZERO;

public:
	float x;
	float y;
	float z;
	float w;

// 0,0 이미지를 만들려고 하면 true
public:
	bool IsZero2D() const
	{
		return x == 0.0f && y == 0.0f;
	}

// 자료형 -> int로 형변환
public:
	int ix() const
	{
		return static_cast<int>(x);
	}

	int iy() const
	{
		return static_cast<int>(y);
	}

	int iz() const
	{
		return static_cast<int>(z);
	}

	int iw() const
	{
		return static_cast<int>(w);
	}

	// 중앙 좌표 -> 오른쪽 아래 좌표 - (위치 * 0.5)
	// 절반 크기를 만들어준다 
	int hix() const
	{
		return static_cast<int>(x * 0.5f);
	}

	int hiy() const
	{
		return static_cast<int>(y * 0.5f);
	}
	
	int hiz() const
	{
		return static_cast<int>(z * 0.5f);
	}

	// 좌표 절반을 리턴 (중심)
	float4 Half() const
	{
		return { x * 0.5f, y * 0.5f, z * 0.5f, 1.0f };
	}
	
	// 대각선 (빗변)의 길이
	float Len2D() const
	{
		// sqrtf 제곱근 구해줍니다.
		return sqrtf((x * x) + (y * y));
	}

	// 방향을 유지한 길이가 1인 단위 벡터
	void Normal2D()
	{
		float Len = Len2D();
		if (0 == Len)
		{
			return;
		}

		x /= Len;
		y /= Len;

		return;
	}

	void Range2D(float _Max)
	{
		Normal2D();

		x *= _Max;
		y *= _Max;
		return;
	}


	float4 operator-(const float4 _Other) const
	{
		return{ x - _Other.x, y - _Other.y, z - _Other.z, 1.0f };
	}

	// 모든 원소를 - 로
	float4 operator-() const
	{
		return { -x, -y, -z, 1.0f };
	}

	float4 operator+(const float4 _Other) const
	{
		return{ x + _Other.x, y + _Other.y, z + _Other.z, 1.0f };
	}

	float4 operator*(const float _Value) const
	{
		return{ x * _Value, y * _Value * _Value, 1.0f };
	}

	float4& operator+=(const float4 _Other)
	{
		x += _Other.x;
		y += _Other.y;
		z += _Other.z;

		return *this;
	}

	float4& operator-=(const float4& _Other)
	{
		x -= _Other.x;
		y -= _Other.y;
		z -= _Other.z;

		return *this;
	}

	float4& operator*=(const float _Other)
	{
		x *= _Other;
		y *= _Other;
		z *= _Other;

		return *this;
	}


	float4& operator*=(const float4& _Other)
	{
		x *= _Other.x;
		y *= _Other.y;
		z *= _Other.z;

		return *this;
	}

	bool CompareInt2D(const float4& _Value)
	{
		return ix() == _Value.ix() && iy() == _Value.iy();
	}

	bool CompareInt3D(const float4& _Value)
	{
		return ix() == _Value.ix() &&
			iy() == _Value.iy() &&
			iz() == _Value.iz();
	}

	// float4의 생성자
public:
	float4()
		: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{

	}
	float4(float _x, float _y)
		: x(_x), y(_y), z(0.0f), w(1.0f)
	{

	}
	float4(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z), w(1.0f)
	{

	}
	float4(float _x, float _y, float _z, float _w) 
		: x(_x), y(_y), z(_z), w(_w)
	{

	}
};

// Actor의 크기 및 좌표를 받아, 중앙 기준으로 기본 사각형을 그린다 
struct GameEngineRect
{
public:
	float4 Pos;
	float4 Scale;

public:
	// 왼쪽 위 x
	int CenterLeft() const
	{
		return Pos.ix() - Scale.hix();
	}

	// 오른쪽 아래 x
	int CenterRight() const
	{
		return Pos.ix() + Scale.hix();
	}

	// 왼쪽 위 y
	int CenterTop() const 
	{
		return Pos.iy() - Scale.hiy();
	}

	// 오른쪽 아래 y
	int CenterBot() const
	{
		return Pos.iy() + Scale.hiy();
	}

	bool OverLap(const GameEngineRect& _Other)
	{
		if (CenterBot() < _Other.CenterTop())
		{
			return false;
		}

		if (CenterTop() > _Other.CenterBot())
		{
			return false;
		}

		if (CenterRight() < _Other.CenterLeft())
		{
			return false;
		}

		if (CenterLeft() > _Other.CenterRight())
		{
			return false;
		}

		return true;
	}

public:
	GameEngineRect(float4 _Pos, float4 _Scale)
		: Pos(_Pos)
		, Scale(_Scale)
	{

	}
};