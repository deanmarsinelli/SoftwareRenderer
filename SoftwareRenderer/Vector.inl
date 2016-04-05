/*
	Vector.inl
	Author: Dean Marsinelli
*/

const double marginOfError = 0.0001;

//------------------------------------------------
//	Vec2 Definitions
//------------------------------------------------

// Constructors
template<typename T>
Vec2<T>::Vec2() :
	x(0.0), y(0.0)
{
}

template<typename T>
Vec2<T>::Vec2(const Vec2<T>& vec) :
	x(vec.x), y(vec.y)
{
}

template<typename T>
Vec2<T>::Vec2(const T& x_, const T& y_) :
	x(x_), y(y_)
{
}


// Setters
template<typename T>
void Vec2<T>::Set(const T& x_, const T& y_)
{
	x = x_;
	y = y_;
}

template<typename T>
void Vec2<T>::Set(const Vec2<T>& vec)
{
	x = vec.x;
	y = vec.y;
}

// Translate the vector
template<typename T>
void Vec2<T>::Translate(const T& x_, const T& y_)
{
	x += x_;
	y += y_;
}

// Overloaded Operators
template<typename T>
Vec2<T>& Vec2<T>::operator+=(const Vec2<T>& vec)
{
	x += vec.x;
	y += vec.y;

	return *this;
}

template<typename T>
Vec2<T>& Vec2<T>::operator-=(const Vec2<T>& vec)
{
	x -= vec.x;
	y -= vec.y;

	return *this;
}

template<typename T>
Vec2<T>& Vec2<T>::operator*=(const Vec2<T>& vec)
{
	x *= vec.x;
	y *= vec.y;

	return *this;
}

template<typename T>
Vec2<T>& Vec2<T>::operator/=(const Vec2<T>& vec)
{
	x /= vec.x;
	y /= vec.y;

	return *this;
}

// Equality operator
template<typename T>
bool Vec2<T>::operator==(const Vec2<T>& vec) const
{
	return (
		(((vec.x - marginOfError) < x) && (x < (vec.x + marginOfError))) &&
		(((vec.y - marginOfError) < y) && (y < (vec.y + marginOfError)))
		);
}

// Inequality operator
template<typename T>
bool Vec2<T>::operator!=(const Vec2<T>& vec) const
{
	return (!(*this == vec));
}

// Assignment operator
template<typename T>
Vec2<T>& Vec2<T>::operator=(const Vec2<T>& vec)
{
	// check for self assignment
	if (this != &vec)
		Set(vec);
	return *this;
}

// Distance
template<typename T>
T Vec2<T>::Distance(const Vec2<T>& vec) const
{
	return sqrt((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y));
}

// Length from the origin
template<typename T>
T Vec2<T>::Length() const
{
	return sqrt(x * x + y * y);
}

// Dot product
template<typename T>
T Vec2<T>::DotProduct(const Vec2<T>& vec) const
{
	return (x * vec.x + y * vec.y);
}

// Return a normalized vector
template<typename T>
Vec2<T> Vec2<T>::Normal() const
{
	if (Length())
	{
		const T length = 1 / Length();
		return Vec2<T>(x * length, y * length);
	}

	return Vec2<T>(0, 0);
}

// Normalize
template<typename T>
void Vec2<T>::Normalize()
{
	if (Length())
	{
		const T length = 1 / Length();
		x *= length;
		y *= length;
	}
}


//------------------------------------------------
//	Vec3 Definitions
//------------------------------------------------

// Constructors
template<typename T>
Vec3<T>::Vec3() :
	x(0.0), y(0.0), z(0.0)
{ 
}

template<typename T>
Vec3<T>::Vec3(const Vec3<T>& vec) :
	x(vec.x), y(vec.y), z(vec.z)
{ 
}

template<typename T>
Vec3<T>::Vec3(const T& x_, const T& y_, const T& z_) :
	x(x_), y(y_), z(z_)
{ 
}

// Setters
template<typename T>
void Vec3<T>::Set(const T& x_, const T& y_, const T& z_)
{
	x = x_;
	y = y_;
	z = z_;
}

template<typename T>
void Vec3<T>::Set(const Vec3<T>& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

// Translate the vector
template<typename T>
void Vec3<T>::Translate(const T& x_, const T& y_, const T& z_)
{
	x += x_;
	y += y_;
	z += z_;
}

// Overloaded operators
template<typename T>
Vec3<T>& Vec3<T>::operator+=(const Vec3<T>& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;

	return *this;
}

template<typename T>
Vec3<T>& Vec3<T>::operator-=(const Vec3<T>& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;

	return *this;
}

template<typename T>
Vec3<T>& Vec3<T>::operator*=(const Vec3<T>& vec)
{
	x *= vec.x;
	y *= vec.y;
	z *= vec.z;

	return *this;
}

template<typename T>
Vec3<T>& Vec3<T>::operator/=(const Vec3<T>& vec)
{
	x /= vec.x;
	y /= vec.y;
	z /= vec.z;

	return *this;
}

// Equality operator
template<typename T>
bool Vec3<T>::operator==(const Vec3<T>& vec) const
{
	return (
		(((vec.x - marginOfError) < x) && (x < (vec.x + marginOfError))) &&
		(((vec.y - marginOfError) < y) && (y < (vec.y + marginOfError))) &&
		(((vec.z - marginOfError) < z) && (z < (vec.z + marginOfError)))
		);
}

// Inequality operator
template<typename T>
bool Vec3<T>::operator!=(const Vec3<T>& vec) const
{
	return (!(*this == vec));
}

// Assignment operator
template<typename T>
Vec3<T>& Vec3<T>::operator=(const Vec3<T>& vec)
{
	// check for self assignment
	if (this != &vec)
		Set(vec);
	return *this;
}

// Distance
template<typename T>
T Vec3<T>::Distance(const Vec3<T>& vec) const
{
	return sqrt((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y) + (vec.z - z) * (vec.z - z));
}

// Length from the origin
template<typename T>
T Vec3<T>::Length() const
{
	return sqrt(x * x + y * y + z * z);
}

// Dot product
template<typename T>
T Vec3<T>::DotProduct(const Vec3<T>& vec) const
{
	return (x * vec.x + y * vec.y + z * vec.z);
}

// Cross product
template<typename T>
Vec3<T> Vec3<T>::CrossProduct(const Vec3<T>& vec) const
{
	return Vec3<T>(
		(y * vec.z) - (z * vec.y),
		(z * vec.x) - (x * vec.z),
		(x * vec.y) - (y * vec.x)
		);
}

// Normal angle
template<typename T>
Vec3<T> Vec3<T>::Normal() const
{
	if (Length())
	{
		const T length = 1 / Length();
		return Vec3<T>(x * length, y * length, z * length);
	}

	return Vec3<T>(0, 0, 0);
}

// Normalize
template<typename T>
void Vec3<T>::Normalize()
{
	if (Length())
	{
		const T length = 1 / Length();
		x *= length;
		y *= length;
		z *= length;
	}
}



//------------------------------------------------
//	Vec4 Definitions
//------------------------------------------------

template<typename T>
Vec4<T>::Vec4() :
	x(0.0), y(0.0), z(0.0), w(0.0)
{
}

template<typename T>
Vec4<T>::Vec4(const Vec3<T>& vec) :
	x(vec.x), y(vec.y), z(vec.z), w(1.0)
{
}

template<typename T>
Vec4<T>::Vec4(const Vec4<T>& vec) :
	x(vec.x), y(vec.y), z(vec.z), w(vec.w)
{
}

template<typename T>
Vec4<T>::Vec4(const T& x_, const T& y_, const T& z_, const T& w_) :
	x(x_), y(y_), z(z_), w(w_)
{
}

template<typename T>
void Vec4<T>::Set(const T& x_, const T& y_, const T& z_, const T& w_)
{
	x = x_;
	y = y_;
	z = z_;
	w = 1.0;
}

template<typename T>
void Vec4<T>::Set(const Vec4<T>& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	w = vec.w;
}

template<typename T>
void Vec4<T>::Translate(const T& x_, const T& y_, const T& z_)
{
	x += x_;
	y += y_;
	z += z_;
}

template<typename T>
void Vec4<T>::Translate(const T& x_, const T& y_, const T& z_, const T& w_)
{
	x += x_;
	y += y_;
	z += z_;
	w += w_;
}

template<typename T>
Vec4<T>& Vec4<T>::operator+=(const Vec4<T>& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	w += vec.w;

	return *this;
}

template<typename T>
Vec4<T>& Vec4<T>::operator-=(const Vec4<T>& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	w -= vec.w;

	return *this;
}

template<typename T>
Vec4<T>& Vec4<T>::operator*=(const Vec4<T>& vec)
{
	x *= vec.x;
	y *= vec.y;
	z *= vec.z;
	w *= vec.w;

	return *this;
}

template<typename T>
Vec4<T>& Vec4<T>::operator/=(const Vec4<T>& vec)
{
	x /= vec.x;
	y /= vec.y;
	z /= vec.z;
	w /= vec.w;

	return *this;
}

template<typename T>
bool Vec4<T>::operator==(const Vec4<T>& vec) const
{
	return (
		(((vec.x - marginOfError) < x) && (x < (vec.x + marginOfError))) &&
		(((vec.y - marginOfError) < y) && (y < (vec.y + marginOfError))) &&
		(((vec.z - marginOfError) < z) && (z < (vec.z + marginOfError))) &&
		(((vec.w - marginOfError) < w) && (w < (vec.w + marginOfError)))
		);
}

template<typename T>
bool Vec4<T>::operator!=(const Vec4<T>& vec) const
{
	return (!(*this == vec));
}

template<typename T>
Vec4<T>& Vec4<T>::operator=(const Vec4<T>& vec)
{
	// check for self assignment
	if (this != &vec)
		Set(vec);

	return *this;
}

template<typename T>
T Vec4<T>::Distance(const Vec4<T>& vec) const
{
	return sqrt((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y) + (vec.z - z) * (vec.z - z) + (vec.w - w) * (vec.w - w));
}

template<typename T>
T Vec4<T>::Length() const
{
	return sqrt(x * x + y * y + z * z + w * w);
}

template<typename T>
T Vec4<T>::DotProduct(const Vec4<T>& vec) const
{
	return (x * vec.x + y * vec.y + z * vec.z + w * vec.w);
}

template<typename T>
Vec4<T> Vec4<T>::Normal() const
{
	if (Length())
	{
		const T length = 1 / Length();
		return Vec4<T>(x * length, y * length, z * length, w * length);
	}

	return Vec4<T>(0, 0, 0, 0);
}

template<typename T>
void Vec4<T>::Normalize()
{
	if (Length())
	{
		const T length = 1 / Length();
		x *= length;
		y *= length;
		z *= length;
		w *= length;
	}
}