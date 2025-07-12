struct Vector
{
	float x, z, y;

	Vector operator+(const Vector & v) const
	{
		return
		{
		x + v.x, z + v.z, y + v.y};
	}

	Vector operator-(const Vector & v)const
	{
		return
		{
		x - v.x, z - v.z, y - v.y};
	}

	Vector operator*(float scalar)const
	{
		return
		{
		x *scalar, z * scalar, y * scalar};
	}

	Vector operator/(float scalar)const
	{
		return
		{
		x / scalar, z / scalar, y / scalar};
	}

	bool operator!=(const Vector & v)const
	{
		return x != v.x || z != v.z || y != v.y;
	}

	bool operator==(const Vector & v)const
	{
		return x == v.x || z == v.z || y == v.y;
	}
};
