#include "Vector.h"

Vector::Vector()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector::Vector(float x1, float y1, float z1)
{
	x = x1;
	y = y1;
	z = z1;
}

Vector::Vector(const Vector& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

Vector Vector::operator+(const Vector& vec)
{
	//Returns a new vector summing the values for each component with the 
	//corresponding component in the added vector

	return Vector(x + vec.x, y + vec.y, z + vec.z);
}

Vector& Vector::operator+=(const Vector& vec)
{
	//Returns ‘this’ pointer (i.e. self-reference summing the values for 
	//each component with the corresponding component in the added vector

	x += vec.x;
	y += vec.y;
	z += vec.z;

	return *this;
}

Vector Vector::operator-(const Vector& vec)
{
	return Vector(x - vec.x, y - vec.y, z - vec.z);
}

Vector& Vector::operator-=(const Vector& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;

	return *this;
}

Vector Vector::operator*(float value)
{
	return Vector(x * value, y * value, z * value);
}

Vector& Vector::operator*=(float value)
{
	x *= value;
	y *= value;
	z *= value;

	return *this;
}

Vector Vector::operator/(float value)
{
	assert(value != 0); //prevent devide by 0

	return Vector(x / value, y / value, z / value);
}

Vector& Vector::operator/=(float value)
{
	assert(value != 0);

	x /= value;
	y /= value;
	z /= value;

	return *this;
}

Vector& Vector::operator=(const Vector &vec)
{
	return Vector(x = vec.x, y = vec.y, z = vec.z);
}

float Vector::dot_product(const Vector& vec)
{
	return (x * vec.x + y * vec.y + z * vec.z);
}

Vector Vector::cross_product(const Vector& vec)
{
	float ni = y * vec.z - z * vec.y;
	float nj = z * vec.x - x * vec.z;
	float nk = x * vec.y - y * vec.x;

	return Vector(ni, nj, nk);
}

float Vector::magnitude()
{
	return sqrt((x * x) + (y * y) + (z * z));
}

float Vector::square()
{
	return x * x + y * y + z * z;
}

Vector Vector::normalization()
{
	float mag = magnitude();
	return Vector(x / mag, y / mag, z / mag);

}

float Vector::distance(const Vector &vec)
{
	return sqrt(pow(vec.x - this->x, 2) + pow(vec.y - this->y, 2) + pow(vec.z - this->z, 2));
}

float Vector::show_X()
{
	return x;
}
float Vector::show_Y()
{
	return y;
}
float Vector::show_Z()
{
	return z;
}
void Vector::disp()
{
	cout << x << " " << y << " " << z << endl;
}

float Vector::lenth()
{
	return sqrt(pow(x, 2) + pow(y,2) + pow(z, 2));
}
