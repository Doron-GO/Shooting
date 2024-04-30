#pragma once

struct Vector2
{

	float x, y; //float��pos

	int intx, inty,intz;//int��pos
	int  Magnitude()const;
	///���K��(�傫�����P��)���܂�
	void Normalize();
	///���K���x�N�g����Ԃ��܂�
	Vector2 Normalized();
	void operator*=(float scale);
	void operator+=(const Vector2& v);

	void operator+=(float scale);


};

//�����ł̕�����₷���̂��߂ɖ��O��Position2�ɂ��Ă��܂�
typedef Vector2 Position2;



Vector2 operator+(const Vector2& va, const Vector2 vb);
Vector2 operator*=(const Vector2& va, const Vector2& vb);
Vector2 operator*(const Vector2& va, float scale);
Vector2 operator-(const Vector2& va, const Vector2 vb);

