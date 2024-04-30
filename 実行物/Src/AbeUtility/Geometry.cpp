#include<DxLib.h>
#include<cmath>
#include "Geometry.h"


int Vector2::Magnitude() const
{
	return hypot(x, y);
}

void
Vector2::Normalize() {
	float mag = Magnitude();
	x /= mag;
	y /= mag;
}

void
Vector2::operator+=(const Vector2& v) {

	x += v.x;
	y += v.y;

}

void Vector2::operator+=(float scale)
{
	x += scale;
	y += scale;

}


Vector2 Vector2::Normalized()
{
	float mag = Magnitude();
	return Vector2(x / mag, y / mag);
}

void
Vector2::operator*=(float scale) {

	x *= scale;
	y *= scale;
}

Vector2 operator+(const Vector2& va, const Vector2 vb) {
	return { va.x + vb.x,va.y + vb.y };
}

Vector2 operator*=(const Vector2& va, const Vector2& vb)
{
	return{ va.x * vb.x,va.y * vb.y };
}

Vector2 operator*(const Vector2& va, float scale)
{
	return{ va.x * scale, va.y * scale };
}

Vector2 operator-(const Vector2& va, const Vector2 vb) {
	return { va.x - vb.x,va.y - vb.y };

}

