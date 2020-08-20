#pragma once
#include<iostream>
#include<math.h>
#include<assert.h>
using namespace std;

class Vector
{
public:

	float x, y, z;

	Vector();
	Vector(float x1, float y1, float z1 = 0);
	Vector(const Vector& vec);
	

	Vector operator+(const Vector& vec);   //addition
	Vector& operator+=(const Vector& vec);//assign new result to vector
	Vector operator-(const Vector& vec); //substraction
	Vector& operator-=(const Vector& vec);//assign new result to vector
	Vector operator*(float value);    //multiplication
	Vector& operator*=(float value);  //assign new result to vector.
	Vector operator/(float value);    //division
	Vector& operator/=(float value);  //assign new result to vector
	Vector& operator=(const Vector& vec);

	float dot_product(const Vector& vec); //scalar dot_product
	Vector cross_product(const Vector& vec); //cross_product
	Vector normalization();   //normalized vector

	float square(); //gives square of the vector
	float distance(const Vector& vec); //distance between two vectors
	float magnitude();  //magnitude of the vector


	float show_X(); //return x
	float show_Y(); //return y
	float show_Z(); //return z
	void disp();    //display value of vectors

	float lenth();
};

