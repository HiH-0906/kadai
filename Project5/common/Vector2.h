#pragma once
// é©çÏ√›Ãﬂ⁄∞ƒ
template<class T> class Vector2Template
{
public:
	Vector2Template();
	Vector2Template(T x, T y);
	~Vector2Template();
	T x;
	T y;

	// ë„ì¸ââéZéq
	Vector2Template& operator = (const Vector2Template& vec);

	// ìYÇ¶éöââéZéq
	T& operator [] (T i);

	// î‰ärââéZéq
	bool operator == (const Vector2Template& vec) const;
	bool operator != (const Vector2Template& vec) const;
	bool operator > (const Vector2Template& vec) const;
	bool operator >= (const Vector2Template& vec) const;
	bool operator < (const Vector2Template& vec) const;
	bool operator <= (const Vector2Template& vec) const;

	// íPçÄââéZéq
	Vector2Template& operator += (const Vector2Template& vec);
	Vector2Template& operator -= (const Vector2Template& vec);
	Vector2Template& operator *= (const Vector2Template& vec);
	Vector2Template& operator /= (const Vector2Template& vec);
	Vector2Template& operator *= (T k);
	Vector2Template& operator /= (T k);
	Vector2Template operator + () const;
	Vector2Template operator - () const;
};

// Õﬁ∏ƒŸÇÃââéZ

// Vector2 + int
template<class T>
Vector2Template<T> operator+(const Vector2Template<T>& u, T k);
// Vector2 - int
template<class T>
Vector2Template<T> operator-(const Vector2Template<T>& u, T k);
// Vector2 * int
template<class T>
Vector2Template<T> operator*(const Vector2Template<T>& u, T k);
// Vector2 / int
template<class T>
Vector2Template<T> operator/(const Vector2Template<T>& u, T k);
// Vector2 % int
template<class T>
Vector2Template<T> operator%(const Vector2Template<T>& u, T k);

// Vector2 + Vector2
template<class T>
Vector2Template<T> operator+(const Vector2Template<T>& u, const Vector2Template<T>& v);
// Vector2 - Vector2
template<class T>
Vector2Template<T> operator-(const Vector2Template<T>& u, const Vector2Template<T>& v);
// Vector2 * Vector2
template<class T>
Vector2Template<T> operator*(const Vector2Template<T>& u, const Vector2Template<T>& v);
// Vector2 / Vector2
template<class T>
Vector2Template<T> operator/(const Vector2Template<T>& u, const Vector2Template<T>& v);
// Vector2 % Vector2
template<class T>
Vector2Template<T> operator%(const Vector2Template<T>& u, const Vector2Template<T>& v);

// int * Vector2
template<class T>
Vector2Template<T> operator*(int k, const Vector2Template<T>& v);

using Vector2 = Vector2Template<int>;
using Vector2Dbl = Vector2Template<double>;
using Vector2Flt = Vector2Template<float>;

#include <common/Detail/Vector2.h>