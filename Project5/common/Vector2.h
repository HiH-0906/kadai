#pragma once
#include <cmath>
// ©μΓέΜίΪ°Δ
template<class T> class Vector2Template
{
public:
	Vector2Template();
	Vector2Template(T x, T y);
	~Vector2Template();
	T x;
	T y;

	// γόZq
	Vector2Template& operator = (const Vector2Template& vec);

	// Y¦Zq
	T& operator [] (T i);

	// δrZq
	bool operator == (const Vector2Template& vec) const;
	bool operator != (const Vector2Template& vec) const;
	bool operator > (const Vector2Template& vec) const;
	bool operator >= (const Vector2Template& vec) const;
	bool operator < (const Vector2Template& vec) const;
	bool operator <= (const Vector2Template& vec) const;

	// PZq
	Vector2Template& operator += (const Vector2Template& vec);
	Vector2Template& operator -= (const Vector2Template& vec);
	Vector2Template& operator *= (const Vector2Template& vec);
	Vector2Template& operator /= (const Vector2Template& vec);
	Vector2Template& operator *= (T k);
	Vector2Template& operator /= (T k);
	Vector2Template operator + () const;
	Vector2Template operator - () const;
};

// ΝήΈΔΩΜZ

// Vector2T + T
template<class T>
Vector2Template<T> operator+(const Vector2Template<T>& u, T k);
// Vector2T - T
template<class T>
Vector2Template<T> operator-(const Vector2Template<T>& u, T k);
// Vector2T * T
template<class T>
Vector2Template<T> operator*(const Vector2Template<T>& u, T k);
// Vector2T / T
template<class T>
Vector2Template<T> operator/(const Vector2Template<T>& u, T k);
// Vector2T % T
template<class T>
Vector2Template<T> operator%(const Vector2Template<T>& u, T k);

// Vector2T + Vector2T
template<class T>
Vector2Template<T> operator+(const Vector2Template<T>& u, const Vector2Template<T>& v);
// Vector2T - Vector2T
template<class T>
Vector2Template<T> operator-(const Vector2Template<T>& u, const Vector2Template<T>& v);
// Vector2T * Vector2T
template<class T>
Vector2Template<T> operator*(const Vector2Template<T>& u, const Vector2Template<T>& v);
// Vector2T / Vector2T
template<class T>
Vector2Template<T> operator/(const Vector2Template<T>& u, const Vector2Template<T>& v);
// Vector2T % Vector2T
template<class T>
Vector2Template<T> operator%(const Vector2Template<T>& u, const Vector2Template<T>& v);

// T * Vector2T
template<class T>
Vector2Template<T> operator*(int k, const Vector2Template<T>& v);

using Vector2    = Vector2Template<int>;
using Vector2Dbl = Vector2Template<double>;
using Vector2Flt = Vector2Template<float>;

// βΞlζΎ
template<class T>
Vector2Template<T>abs(const Vector2Template<T>& u);

#include <common/Detail/Vector2.h>