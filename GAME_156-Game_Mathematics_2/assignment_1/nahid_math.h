/*
 * Nahid Sekander
 * n01001831
 * GAME 156
 * Assignment #1
 * */


#include <math.h>
#include <iostream>


//Part 1
struct vec_3
{
	//Member variables 
	float x, y, z;
	//Default constructor
	//vec_3{}
	//

/*
	vec_3()
	{
		x = 0;
		y = 0;
		z = 0;
	}


	vec_3(float x_pos, float y_pos, float z_pos)
	{
		x = x_pos;
		y = y_pos;
		z = z_pos;
	}
*/

//	Vector scalar multiplication

	vec_3& operator *= (const float scalar)
	{
//		vec_3 v;

		x = x * scalar;
		y = y * scalar;
		z = z * scalar;
	
		return *this; 
	}

//	Vector scalar division

	vec_3& operator /= (float scalar)
	{
		x = x / scalar;
		y = y / scalar;
		z = z / scalar;

		return *this;	
	}


//	Vector addition
	vec_3& operator += (const vec_3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}

//	Vector substraction
	vec_3& operator -= (const vec_3& v)
	{
		x = -v.x;
		y = -v.y;
		z = -v.z;

		return *this;
	}

//	Find the magnitude of vector
	float magnitude(const vec_3& v)
	{
		return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
	}


//	Find the normal vector
	vec_3 normalize(const vec_3& v)
	{
		//return vec_3(v.x / magnitude(v), v.y / magnitude(v), v.z / magnitude(v));	
		return vec_3{v.x / magnitude(v), 
			     v.y / magnitude(v), 
			     v.z / magnitude(v)};	
	}

//	Print out vector
	void print_vec()
	{
		std::cout << "vec_3 (" << x << ", " << y << ", " << z << ")"  << std::endl;	
	
	}

//	Calculate the dot product of vecotr
	float dot(const vec_3& a, const vec_3& b)
	{
		return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
	}

//	Calculate the cross vector 
	vec_3 cross(const vec_3& a, const vec_3& b)
	{
		//return vec_3(0,0,0);
		return vec_3{(a.y * b.z) - (a.z * b.y),
			     (a.z * b.x) - (a.x * b.z),
			     (a.x * b.y) - (a.y * b.x)};

	}
};


	//Add two vectors together
	inline vec_3 operator + (const vec_3& a, const vec_3& b)
	{
		//return vec_3(a.x + b.x, a.y + b.y, a.z + b.z);
		return vec_3{a.x + b.x, a.y + b.y, a.z + b.z};
	}

	//Substract two vectors 
	inline vec_3 operator - (const vec_3& a, const vec_3& b)
	{
		//return vec_3(a.x - b.x, a.y - b.y, a.z - b.z);
		return vec_3{a.x - b.x, a.y - b.y, a.z - b.z};
	}


//Part 2
struct vec_4
{
	//Member variables 
	float x, y, z, w;

	//Default constructor
	vec_4()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 1;
	}

	//Intitialzied constructor
	vec_4(float x_pos, float y_pos, float z_pos, float w_)
	{
		x = x_pos;
		y = y_pos;
		z = z_pos;
		w = w_;
	}

	//Scalar multiplication
	vec_4& operator *= (float scalar)
	{

		x = x * scalar;
		y = y * scalar;
		z = z * scalar;
		w = w * scalar;	
		return *this; 
	}

	//Scalar division
	vec_4& operator /= (float scalar)
	{
		x = x / scalar;
		y = y / scalar;
		z = z / scalar;
		w = w / scalar;

		return *this;	
	}

	
//	Vector addition
	vec_4& operator += (vec_4& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;

		return *this;
	}

//	Vector substraction 
	vec_4& operator -= (vec_4& v)
	{
		x = -v.x;
		y = -v.y;
		z = -v.z;
		w = -v.w;

		return *this;
	}

//	Calculate maginitude of vector
	float magnitude(const vec_4& v)
	{
		return sqrt(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w);
	}

//	Find the normal vector
	vec_4 normalize(const vec_4& v)
	{
		return vec_4(v.x / magnitude(v), v.y / magnitude(v), v.z / magnitude(v), v.w / magnitude(v));	
	}

//	Print out vector
	void print_vec()
	{
		std::cout << "vec_4 (" << x << ", " << y << ", " << z << ", " << w << ")"  << std::endl;	
	
	}

//	Calculate dot product
	float dot(const vec_4& a, const vec_4& b)
	{
		return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w));
	}
};



	//
	inline vec_4 operator + (const vec_4& a, const vec_4& b)
	{
		return vec_4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
	}

	inline vec_4 operator - (const vec_4& a, const vec_4& b)
	{
		return vec_4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
	}


