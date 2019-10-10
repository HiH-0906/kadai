#pragma once
class Vector2
{
public:
	Vector2();
	Vector2(int x, int y);
	~Vector2();
	int x;
	int y;

	// ‘ã“ü‰‰ŽZŽq
	Vector2& operator = (const Vector2& vec);

	// “Y‚¦Žš‰‰ŽZŽq
	int& operator [] (int i);

	// ”äŠr‰‰ŽZŽq
	bool operator == (const Vector2& vec) const;
	bool operator != (const Vector2& vec) const;
	bool operator > (const Vector2& vec) const;
	bool operator >= (const Vector2& vec) const;
	bool operator < (const Vector2& vec) const;
	bool operator <= (const Vector2& vec) const;

	// ’P€‰‰ŽZŽq
	Vector2& operator += (const Vector2& vec);
	Vector2& operator -= (const Vector2& vec);
	Vector2& operator *= (const Vector2& vec);
	Vector2& operator /= (const Vector2& vec);
	Vector2& operator *= (int k);
	Vector2& operator /= (int k);
	Vector2 operator + () const;
	Vector2 operator - () const;
};

// ÍÞ¸ÄÙ‚Ì‰‰ŽZ

// Vector2 + int
Vector2 operator+(const Vector2& u, int k);
// Vector2 - int
Vector2 operator-(const Vector2& u, int k);
// Vector2 * int
Vector2 operator*(const Vector2& u, int k);
// Vector2 / int
Vector2 operator/(const Vector2& u, int k);
// Vector2 % int
Vector2 operator%(const Vector2& u, int k);

// Vector2 + Vector2
Vector2 operator+(const Vector2& u, const Vector2& v);
// Vector2 - Vector2
Vector2 operator-(const Vector2& u, const Vector2& v);
// Vector2 * Vector2
Vector2 operator*(const Vector2& u, const Vector2& v);
// Vector2 / Vector2
Vector2 operator/(const Vector2& u, const Vector2& v);
// Vector2 % Vector2
Vector2 operator%(const Vector2& u, const Vector2& v);

// int * Vector2
Vector2 operator*(int k, const Vector2& v);