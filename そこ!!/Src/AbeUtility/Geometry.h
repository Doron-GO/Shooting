#pragma once

struct Vector2
{

	float x, y; //floatのpos

	int intx, inty,intz;//intのpos
	int  Magnitude()const;
	///正規化(大きさを１に)します
	void Normalize();
	///正規化ベクトルを返します
	Vector2 Normalized();
	void operator*=(float scale);
	void operator+=(const Vector2& v);

	void operator+=(float scale);


};

//自分での分かりやすさのために名前をPosition2にしています
typedef Vector2 Position2;



Vector2 operator+(const Vector2& va, const Vector2 vb);
Vector2 operator*=(const Vector2& va, const Vector2& vb);
Vector2 operator*(const Vector2& va, float scale);
Vector2 operator-(const Vector2& va, const Vector2 vb);

