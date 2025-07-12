
struct EulerAngles
{
	float x, z, y;

	EulerAngles operator+(const EulerAngles & v) const
	{
		return
		{
		x + v.x, z + v.z, y + v.y};
	}

	EulerAngles operator-(const EulerAngles & v)const
	{
		return
		{
		x - v.x, z - v.z, y - v.y};
	}

	EulerAngles operator*(float scalar)const
	{
		return
		{
		x *scalar, z * scalar, y * scalar};
	}

	EulerAngles operator/(float scalar)const
	{
		return
		{
		x / scalar, z / scalar, y / scalar};
	}

	EulerAngles & operator+=(const EulerAngles & v)
	{
		x += v.x;
		z += v.z;
		y += v.y;
		return *this;
	}

	EulerAngles & operator-=(const EulerAngles & v)
	{
		x -= v.x;
		z -= v.z;
		y -= v.y;
		return *this;
	}

	EulerAngles & operator*=(float scalar)
	{
		x *= scalar;
		z *= scalar;
		y *= scalar;
		return *this;
	}

	EulerAngles & operator/=(float scalar)
	{
		x /= scalar;
		z /= scalar;
		y /= scalar;
		return *this;
	}

	bool operator!=(const EulerAngles & v)const
	{
		return x != v.x || z != v.z || y != v.y;
	}

	bool operator==(const EulerAngles & v)const
	{
		return x == v.x && z == v.z && y == v.y;
	}
};

struct Quaternion2
{
	float w, x, y, z;

	Quaternion2 operator+(const Quaternion2 & q) const
	{
		return
		{
		w + q.w, x + q.x, y + q.y, z + q.z};
	}

	Quaternion2 operator-(const Quaternion2 & q)const
	{
		return
		{
		w - q.w, x - q.x, y - q.y, z - q.z};
	}

	Quaternion2 operator*(float scalar)const
	{
		return
		{
		w *scalar, x * scalar, y * scalar, z * scalar};
	}

	Quaternion2 operator/(float scalar)const
	{
		return
		{
		w / scalar, x / scalar, y / scalar, z / scalar};
	}

	Quaternion2 & operator+=(const Quaternion2 & q)
	{
		w += q.w;
		x += q.x;
		y += q.y;
		z += q.z;
		return *this;
	}

	Quaternion2 & operator-=(const Quaternion2 & q)
	{
		w -= q.w;
		x -= q.x;
		y -= q.y;
		z -= q.z;
		return *this;
	}

	Quaternion2 & operator*=(float scalar)
	{
		w *= scalar;
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	Quaternion2 & operator/=(float scalar)
	{
		w /= scalar;
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}

	bool operator!=(const Quaternion2 & q)const
	{
		return w != q.w || x != q.x || y != q.y || z != q.z;
	}

	bool operator==(const Quaternion2 & q)const
	{
		return w == q.w && x == q.x && y == q.y && z == q.z;
	}
};