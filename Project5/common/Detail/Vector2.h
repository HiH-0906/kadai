#include "..\Vector2.h"
template<class T>
Vector2Template<T>::Vector2Template()
{
	x = static_cast<T>(0);
	y = static_cast<T>(0);
}

template<class T>
Vector2Template<T>::Vector2Template(T x, T y)
{
	this->x = x;
	this->y = y;
}


template<class T>
Vector2Template<T>::~Vector2Template()
{
}

// ‘ã“ü‰‰ŽZŽq
template<class T>
Vector2Template<T> & Vector2Template<T>::operator=(const Vector2Template<T> & vec)
{
	x = vec.x;
	y = vec.y;
	return *this;
}

// “Y‚¦Žš‰‰ŽZŽq
template<class T>
T & Vector2Template<T>::operator[](T i)
{
	if (i == 0)
	{
		return x;
	}
	else if (i == 1)
	{
		return y;
	}
	else
	{
		return x;
	}
}

// ”äŠr‰‰ŽZŽq
template<class T>
bool Vector2Template<T>::operator==(const Vector2Template<T> & vec) const
{
	return ((this->x == vec.x) && (this->y == vec.y));
}

template<class T>
bool Vector2Template<T>::operator!=(const Vector2Template<T> & vec) const
{
	return !((this->x == vec.x) && (this->y == vec.y));
}

template<class T>
bool Vector2Template<T>::operator>(const Vector2Template<T> & vec) const
{
	return ((this->x > vec.x) && (this->y > vec.y));
}

template<class T>
bool Vector2Template<T>::operator>=(const Vector2Template<T> & vec) const
{
	return ((this->x >= vec.x) && (this->y >= vec.y));
}

template<class T>
bool Vector2Template<T>::operator<(const Vector2Template<T> & vec) const
{
	return ((this->x < vec.x) && (this->y < vec.y));
}

template<class T>
bool Vector2Template<T>::operator<=(const Vector2Template<T> & vec) const
{
	return ((this->x <= vec.x) && (this->y <= vec.y));
}

// ’P€‰‰ŽZŽq
template<class T>
Vector2Template<T> & Vector2Template<T>::operator+=(const Vector2Template<T> & vec)
{
	x += vec.x;
	y += vec.y;
	return *this;
}

template<class T>
Vector2Template<T> & Vector2Template<T>::operator-=(const Vector2Template<T> & vec)
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}

template<class T>
Vector2Template<T> & Vector2Template<T>::operator*=(const Vector2Template<T> & vec)
{
	x *= vec.x;
	y *= vec.y;
	return *this;
}

template<class T>
Vector2Template<T> & Vector2Template<T>::operator/=(const Vector2Template<T> & vec)
{
	x /= vec.x;
	y /= vec.y;
	return *this;
}

template<class T>
Vector2Template<T> & Vector2Template<T>::operator*=(T k)
{
	x *= k;
	y *= k;
	return *this;
}

template<class T>
Vector2Template<T> & Vector2Template<T>::operator/=(T k)
{
	x /= k;
	y /= k;
	return *this;
}

template<class T>
Vector2Template<T> Vector2Template<T>::operator+() const
{
	return *this;
}

template<class T>
Vector2Template<T> Vector2Template<T>::operator-() const
{
	return Vector2Template(-this->x, -this->y);
}

template<class T>
Vector2Template<T> operator+(const Vector2Template<T> & u, T k)
{
	Vector2Template<T> vec;
	vec.x = u.x + k;
	vec.y = u.y + k;
	return vec;
}

template<class T>
Vector2Template<T> operator-(const Vector2Template<T> & u, T k)
{
	Vector2Template<T> vec;
	vec.x = u.x - k;
	vec.y = u.y - k;
	return vec;
}

template<class T>
Vector2Template<T> operator*(const Vector2Template<T> & u, T k)
{
	Vector2Template<T> vec;
	vec.x = u.x * k;
	vec.y = u.y * k;
	return vec;
}

template<class T>
Vector2Template<T> operator/(const Vector2Template<T> & u, T k)
{
	Vector2Template<T> vec;
	vec.x = u.x / k;
	vec.y = u.y / k;
	return vec;
}

template<class T>
Vector2Template<T> operator%(const Vector2Template<T> & u, T k)
{
	Vector2Template<T> vec;
	vec.x = u.x % k;
	vec.y = u.y % k;
	return vec;
}

template<class T>
Vector2Template<T> operator+(const Vector2Template<T> & u, const Vector2Template<T> & v)
{
	Vector2Template<T> vec;
	vec.x = u.x + v.x;
	vec.y = u.y + v.y;
	return vec;
}

template<class T>
Vector2Template<T> operator-(const Vector2Template<T> & u, const Vector2Template<T> & v)
{
	Vector2Template<T> vec;
	vec.x = u.x - v.x;
	vec.y = u.y - v.y;
	return vec;
}

template<class T>
Vector2Template<T> operator*(const Vector2Template<T> & u, const Vector2Template<T> & v)
{
	Vector2Template<T> vec;
	vec.x = u.x * v.x;
	vec.y = u.y * v.y;
	return vec;
}

template<class T>
Vector2Template<T> operator/(const Vector2Template<T> & u, const Vector2Template<T> & v)
{
	Vector2Template<T> vec;
	vec.x = u.x / v.x;
	vec.y = u.y / v.y;
	return vec;
}

template<class T>
Vector2Template<T> operator%(const Vector2Template<T> & u, const Vector2Template<T> & v)
{
	Vector2Template<T> vec;
	vec.x = u.x % v.x;
	vec.y = u.y % v.y;
	return vec;
}

template<class T>
Vector2Template<T> operator*(int k, const Vector2Template<T> & v)
{
	Vector2Template<T> vec;
	vec.x = k * v.x;
	vec.y = k * v.y;
	return vec;
}

template<class T>
inline Vector2Template<T> abs(Vector2Template<T>& vec)
{
	return { abs(vec.x),abs(vec.y) };
}
