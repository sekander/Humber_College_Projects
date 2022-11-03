/*
 * Nahid Sekander
 * n01001831
 * GAME 156
 * Assignment #2
 * */


#include <algorithm>
#include <cmath>
#include <math.h>
#include <iostream>
#include <float.h>

#include <vector>

//Part 1
struct vec_3
{
	//Member variables 
	float x, y, z;
	//Default constructor
	//vec_3{}
	//


	vec_3()
	{
		x = 0;
		y = 0;
		z = 0;
	}


	vec_3(float x_pos, float y_pos, float z_pos = 0.0f)
	{
		x = x_pos;
		y = y_pos;
		z = z_pos;
	}


//	Vector scalar multiplication
	
	vec_3& operator + (const vec_3& v)
	{
		x = x + v.x;
		y = y + v.y;
		z = z + v.z;

		return *this;
	}

	vec_3& operator - (const vec_3& v)
	{
		x = x - v.x;
		y = y - v.y;
		z = z - v.z;

		return *this;
	}
	vec_3& operator *= (const float scalar)
	{
//		vec_3 v;

		x = x * scalar;
		y = y * scalar;
		z = z * scalar;
	
		return *this; 
	}

	vec_3& operator * (const float scalar)
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
	
//	Print out vector
	void print_vec()
	{
		std::cout << "vec_3 (" << x << ", " << y << ", " << z << ")"  << std::endl;	
	
	}

};

//	Find the magnitude of vector
inline	float magnitude(const vec_3& v)
	{
		return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
	}


//	Find the normal vector
	inline vec_3 normalize(const vec_3& v)
	{
		//return vec_3(v.x / magnitude(v), v.y / magnitude(v), v.z / magnitude(v));	
		return vec_3{v.x / magnitude(v), 
			     v.y / magnitude(v), 
			     v.z / magnitude(v)};	
	}


//	Calculate the dot product of vecotr
	inline float dot(const vec_3& a, const vec_3& b)
	{
		return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
	}

//	Calculate the cross vector 
	inline vec_3 cross(const vec_3& a, const vec_3& b)
	{
		//return vec_3(0,0,0);
		return vec_3{(a.y * b.z) - (a.z * b.y),
			     (a.z * b.x) - (a.x * b.z),
			     (a.x * b.y) - (a.y * b.x)};

	}

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

//Matrix Structure
struct matrix_3D
{
	private:
		float n[3][3];

	public:
		matrix_3D() = default;

		//Matrix definition thrugh floats 
		matrix_3D(float n00, float n01, float n02,
			  float n03, float n04, float n05,
			  float n06, float n07, float n08
			 )
		{
		n[0][0] = n00; n[0][1] = n03; n[2][0] = n06;
		n[1][0] = n01; n[1][1] = n04; n[2][1] = n07;
		n[2][0] = n02; n[1][2] = n05; n[2][2] = n08;
		}

		//Matrix definition by 3 vec_3 
		matrix_3D(const vec_3& a, const vec_3& b, const vec_3& c)
		{
		n[0][0]	= a.x; n[0][1]	= a.y; n[0][2]	= a.z;
		n[1][0]	= b.x; n[1][1]	= b.y; n[1][2]	= b.z;
		n[2][0]	= c.x; n[2][1]	= c.y; n[2][2]	= c.z;
		}
		
		void print_matrix3()
		{
			std::cout << "M: \n(\n\tv0( " << n[0][0] << ", " << n[0][1] << ", " << n[0][2] << "),\n"  <<
					"\tv1( "	<< n[1][0] << ", " << n[1][1] << ", " << n[1][2] << "),\n" <<
					"\tv2( "	<< n[2][0] << ", " << n[2][1] << ", " << n[2][2] << ")\n) "  <<
			std::endl;			
		}

		//Return matrix through searching the index 
		float& operator () (int i, int j)
		{
			return n[i][j];
		}	

		//Recturn vector by index 
		vec_3& operator [] (int i)
		{
			return (*reinterpret_cast<vec_3*>(n[i]));
		}
		
		float determinant(matrix_3D& m)
		{
			return (m(0,0) * (m(1,1) * m(2,2) - m(1,2) * m(2,1)) 
				+ m(0,1) * (m(1,2) * m(2,0) - m(1,0) * m(2,2))
				+ m(0, 2) * (m(1,0) * m(2,1) - m(1,1) * m(2,0))) ;
		}



};

		inline matrix_3D operator *(matrix_3D& A, matrix_3D& B)
		{
			return matrix_3D(
					A(0,0) * B(0,0) + A(0,1) * B(1, 0) + A(0,2) * B(2,0),
					A(0,0) * B(0,1) + A(0,1) * B(1, 1) + A(0,2) * B(2,1),
					A(0,0) * B(0,2) + A(0,1) * B(1, 2) + A(0,2) * B(2,2),
					
					A(1,0) * B(0,0) + A(1,1) * B(1, 0) + A(1,2) * B(2,0),
					A(1,0) * B(0,1) + A(1,1) * B(1, 1) + A(1,2) * B(2,1),
					A(1,0) * B(0,2) + A(1,1) * B(1, 2) + A(1,2) * B(2,2),
					
					A(2,0) * B(0,0) + A(2,1) * B(1, 0) + A(2,2) * B(2,0),
					A(2,0) * B(0,1) + A(2,1) * B(1, 1) + A(2,2) * B(2,1),
					A(2,0) * B(0,2) + A(2,1) * B(1, 2) + A(2,2) * B(2,2)
					);	
		}

		inline vec_3 operator * (matrix_3D& M, const vec_3& v)
		{
			return vec_3(
					M(0,0) * v.x + M(0, 1) * v.y + M(0, 2) * v.z, 
					M(1,0) * v.x + M(1, 1) * v.y + M(1, 2) * v.z, 
					M(2,0) * v.x + M(2, 1) * v.y + M(2, 2) * v.z
				    );
		}
		
		inline matrix_3D inverse(matrix_3D& m)
		{
			const vec_3& a = m[0];	
			const vec_3& b = m[1];	
			const vec_3& c = m[2];

			vec_3 r0 = cross(b, c);
			vec_3 r1 = cross(c, a);
			vec_3 r2 = cross(a, b);

			float inverse_determinant = 1.0f/dot(r2, c);

			return matrix_3D(r0.x * inverse_determinant, 
					 r0.y * inverse_determinant, 
					 r0.z * inverse_determinant, 
					 r1.x * inverse_determinant, 
					 r1.y * inverse_determinant, 
					 r1.z * inverse_determinant, 
					 r2.x * inverse_determinant, 
					 r2.y * inverse_determinant, 
					 r2.z * inverse_determinant);
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

};


//	Calculate dot product
	inline float dot(const vec_4& a, const vec_4& b)
	{
		return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w));
	}

	//
	inline vec_4 operator + (const vec_4& a, const vec_4& b)
	{
		return vec_4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
	}

	inline vec_4 operator - (const vec_4& a, const vec_4& b)
	{
		return vec_4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
	}

//Point struct inherits from vec struct 
struct Point3D : vec_3
{
	Point3D() = default;
	Point3D(float a, float b, float c) : vec_3(a, b, c){}


};

//Overload operator to add point and vector
inline Point3D operator +(const Point3D& a, const vec_3& b)
{
	return (Point3D(a.x + b.x, a.y + b.y, a.z + b.z));
}


//Overload operator to substract point and vector
inline Point3D operator -(const Point3D& a, const vec_3& b)
{
	return (Point3D(a.x - b.x, a.y - b.y, a.z - b.z));
}

//Part 1
//struct for ray
struct ray 
{
	//member variables
	// starting point of ray
	vec_3 start;
	//direction of ray
	vec_3 dir;

	//Member variables set 
	ray(vec_3 start_, vec_3 dir_):start(start_), dir(dir_){}

	//Where are we along the Ray?
	vec_3 current_position(float t)
	{
		dir *= t;
		return start + dir;
	}
};

//Part 2
//struct for plane 
struct plane
{
	//member variables
	//represent plane using x, y, z and w as the 4th component 
	float x, y, z, w;

	plane() = default;

	//Set the member variables of the plane
	plane(float nx, float ny, float nz, float d)
	{
		x = nx;
		y = ny;
		z = nz;
		w = d;
	}
	
	//Define the plane using three points that are on the plane
	plane(const vec_3& n, float d)
	{
		x = n.x;
		y = n.y;
		z = n.z;
		d = d;
	}

	void print_plane()
	{
		std::cout << "plane (" << x << ", " << y << ", " << z << ", " << w << ")"  << std::endl;	
	
	}

};

//Overloaded dot product function using plane with vector
inline float dot(const plane& p, const vec_3& v)
{
	return (p.x * v.x + p.y * v.y + p.z * v.z );
}

//Overloaded dot product function using plane with point 
inline float dot(const plane& p, const Point3D& q)
{
	return (p.x * q.x + p.y * q.y + p.z *q.z + p.w);
}

//Find the intersection point of a line passing through this plane 
inline Point3D intersection_line_plane(const Point3D& p, vec_3& v,
				const plane    q )
{
	float fv = dot(q, v);
	float qq = dot(q, p);
	auto s = qq / fv;
	auto n = v * s;
	auto w = p - n;
		return w;
}

//Find the intersection point of a ray passing through this plane 
inline vec_3 intersection_ray_plane(ray& r, const plane& p)
{
	float fv = dot(p, r.dir);
	float qq = dot(p, reinterpret_cast<Point3D&>(r.start));

	auto s = qq / fv;
	auto n = r.dir * s;
	auto intersection = r.start - n;

	return intersection;

}


//Assignmen 3
//
//Part 1
//

//Sphere Struct
struct Sphere
{
	//Member variables
	
	vec_3 position;
	float radius;

	Sphere() = default;

	Sphere(vec_3 _position, float _radius)
	{
		position = _position;
		radius   = _radius;
	}
};

inline static bool RaySphereCollisionDetected(const ray &ray, const Sphere &sphere)
{
	auto a = dot(ray.dir , ray.dir); 
	auto b = 2 * (dot(ray.start, ray.dir));
	auto c = (dot(ray.start, ray.start) - (sphere.radius*sphere.radius));

	auto d = b*b - 4 * (a*c);

	if(d < 0)
		return false;
	if(d > 0)
		return true;
}
inline static vec_3 RaySphereCollisionPoint(const ray &ray, const Sphere &sphere, int point)
{
	auto a = dot(ray.dir , ray.dir); 
	auto b = 2 * (dot(ray.start, ray.dir));
	auto c = (dot(ray.start, ray.start) - (sphere.radius*sphere.radius));
	
	auto t0 = (-b - sqrt((b*b)-4*(a*c)))/(2 * a);
	auto t1 = (-b + sqrt((b*b)-4*(a*c)))/(2 * a);


	auto v = vec_3(ray.dir.x * t0, ray.dir.y * t0, ray.dir.z * t0);
	auto u = vec_3(ray.dir.x * t1, ray.dir.y * t1, ray.dir.z * t1);

	if(point == 1)
		return ray.start + v;
	if(point == 2)
		return ray.start + u;
	

}

//Part 2
//
struct AAB : plane 
{
	//Memeber Variables
	float rx, ry, rz;
	plane p0, p1, p2, p3, p4, p5;

	//A box can be described as 6 planes
	//
	plane box[6];

//	box[0] = plane(1, 0, 0, 0); 

//plane p0(1, 0, 0, 0);
//plane p1(0, 1, 0, 0);
//plane p2(0, 0, 1, 0);
//plane p3(1, 0, 0, 1);
//plane p4(0, 1, 0, 1);
//plane p5(0, 0, 1, 1);

	AAB() = default;

	AAB(float width, float height, float depth)
	{
		rx = width;
		ry = height;
		rz = depth;	
		
		box[0] = plane(1, 0, 0, 0);
		box[1] = plane(0, 1, 0, 0);
		box[2] = plane(0, 0, 1, 0);
		box[3] = plane(1, 0, 0, -rx);
		box[4] = plane(0, 1, 0, -ry);
		box[5] = plane(0, 0, 1, -rz);

		p0 = box[0];
		p1 = box[1];
		p2 = box[2];
		p3 = box[3];
		p4 = box[4];
		p5 = box[5];
	}

	AAB(plane &p0_,
	    plane &p1_,
	    plane &p2_,
	    plane &p3_,
	    plane &p4_,
	    plane &p5_
	    ){
		p0 = p0_;
		p1 = p1_;
		p2 = p2_;
		p3 = p3_;
		p4 = p4_;
		p5 = p5_;

		}


};

//Checks which planes intersects with ray, if condition is true plane is pushed to a vector array for further checking
std::vector<plane> checkRaywihBB(ray &r, AAB &b)
{
	std::vector<plane> planes;
	
	if(r.dir.x != 0)
	{
		if(r.dir.x > 0)
			//Loop through box check each plane for x = 0 test condition
		{
			planes.push_back(b.p0);
		}
		else if (r.dir.x < 0)
			planes.push_back(b.p3);
	}
	
	if(r.dir.y != 0)
	{
		if(r.dir.y > 0)
			planes.push_back(b.p1);
		else if (r.dir.y < 0)
			planes.push_back(b.p4);
	}

	if(r.dir.z != 0)
	{
		if(r.dir.z > 0)
			planes.push_back(b.p2);
		else if (r.dir.z < 0)
			planes.push_back(b.p5);
	}
	return planes;
}

std::vector<plane> sscheckRaywihBB(ray &r, AAB &b)
{
	std::vector<plane> planes;
	
	if(r.dir.x != 0)
	{
		if(r.dir.x > 0)
			//Loop through box check each plane for x = 0 test condition
		{
			for(int i = 0; i < 6; i++)
			{
				if(b.box[i].x == 0)
					planes.push_back(b.box[i]);
			}
		}
		else if (r.dir.x < 0)
		{
			for(int i = 0; i < 6; i++)
			{
				if(b.box[i].x != 0)
					planes.push_back(b.box[i]);
			}
		}
	}
	
	if(r.dir.y != 0)
	{
		if(r.dir.y > 0)
			//Loop through box check each plane for x = 0 test condition
		{
			for(int i = 0; i < 6; i++)
			{
				if(b.box[i].y == 0)
					planes.push_back(b.box[i]);
			}
		}
		else if (r.dir.y < 0)
		{
			for(int i = 0; i > 6; i++)
			{
				if(b.box[i].y != 0)
					planes.push_back(b.box[i]);
			}
		}
	}
	
	if(r.dir.z != 0)
	{
		if(r.dir.z > 0)
			//Loop through box check each plane for x = 0 test condition
		{
			for(int i = 0; i > 6; i++)
			{
				if(b.box[i].z == 0)
					planes.push_back(b.box[i]);
			}
		}
		else if (r.dir.z < 0)
		{
			for(int i = 0; i > 6; i++)
			{
				if(b.box[i].z != 0)
					planes.push_back(b.box[i]);
			}
		}
	}
	return planes;
}

//Assignment 4
//
//Part 1
struct Quaternion
{

	//Quaternion member variables
	float x, y, z, w;

	Quaternion()
	{
	//set all x, y, z to zero, and w to 1
		x = 0;
		y = 0;
		z = 0;
		w = 1;
	}
	Quaternion(float a, float b, float c, float s)
	{
		x = a;
		y = b;
		z = c;
		w = s;	
	}

	//create a rotation quaternion using axis and angle
	Quaternion(vec_3 axis, float angle_in_degree)
	{
		x = axis.x;
		y = axis.y;
		z = axis.z;

		w = angle_in_degree;

	}

	//Print quaternion
	void print_quaternion()
	{
		std::cout << "Quaternion(" << x << ", " << y << ", " << z << ", " << w << ")"  << std::endl;	
	
	}
};

	//overload the * operator to multiply two quaternions
	inline Quaternion operator *(const Quaternion& q1, const Quaternion& q2){
		return (Quaternion(
				q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
				q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x,
				q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w,
				q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z));
	}

	//Return the magnitude of the Quaternion using pythagorans theorem
	inline float Mag(const Quaternion& q)
	{
		return sqrt((q.x * q.x) + (q.y * q.y) + (q.z * q.z) + (q.w * q.w));	
	}

	//Normalize the Quaternion by dividing it by its magnitude
	inline Quaternion Normalize(const Quaternion& q)
	{
		return Quaternion(q.x/Mag(q),q.y/Mag(q),q.z/Mag(q),q.w/Mag(q));
	}

	//Reverse sign on the imaginary part of the quaternion (x, y, z)
	inline Quaternion Conjugate(const Quaternion& q)
	{
		return Quaternion(q.x * -1, q.y * -1, q.z * -1, q.w);
	}

	//Invert the quaternion
	inline Quaternion Inverse(const Quaternion& q)
	{
		auto m = Mag(q);
		auto c = Conjugate(q);

		return Quaternion(c.x/m*m, c.y/m*m, c.z/m*m, c.w/m*m);
	}

	//Rotate a vector using this quaternion
	inline vec_3 rotate(vec_3& vec, Quaternion& q)
	{
		Quaternion temp_q(vec, 0.0);
		auto inv = Inverse(q);
	
		auto r = q * temp_q * inv;

		return vec_3(r.x, r.y, r.z);
	}

	//Convert this quaternion into a rotation matrix
	inline matrix_3D convertToMatrix(Quaternion& q)
	{
		return matrix_3D(  
				  (2 * (q.w*q.w) + (q.x*q.x) - 0.5),
				  (2 * (q.w*q.z) + (q.x*q.y)),
				  (2 * (q.x*q.z) - (q.w*q.y)),

				  (2 * (q.x*q.y) - (q.w*q.z)),	 
				  (2 * (q.w*q.w) + (q.y*q.y) - 0.5),	 				  (2 * (q.w*q.x) + (q.y*q.z)),	 
				
				  (2 * (q.w*q.y) + (q.x*q.z)),	 
				  (2 * (q.y*q.z) - (q.w*q.x)),	 
				  (2 * (q.w*q.w) + (q.z*q.z) - 0.5  ));
	}


//Part 2
//
struct EulerAngles{
	float yaw, pitch, roll;

	EulerAngles()
	{
		yaw = 0.0f;
		pitch = 0.0f;
		roll = 0.0f;
	}

	EulerAngles(float yaw_, float pitch_, float roll_)
	{
		yaw = yaw_;
		pitch = pitch_;
		roll = roll_;
	}

	//Print eulerangle 
	void print_eulerangle()
	{
		std::cout << "EulerAngle(" << yaw << ", " << pitch << ", " << roll << ")"  << std::endl;	
	
	}
};

//https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles#Source_code_2
//
//
//Convert this quaternion into Euler angles
inline EulerAngles fromQuaternionToEulerAngle(Quaternion& q)
{
	EulerAngles angles;
	//roll (x-axis rotation)
	auto sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
	auto cosr_cosp = 1 - 2 * (q.x + q.x + q.y * q.y);

	angles.roll = std::atan2(sinr_cosp, cosr_cosp);

	//pitch (y-axis rotation)
	auto sinp = 2 * (q.w * q.y - q.z * q.x);
	if(std::abs(sinp) >= 1)
		angles.pitch = std::copysign(M_PI /2, sinp);
	//use 90 degress if out of range
	else
		angles.pitch = std::asin(sinp);

	//yaw (z-axis rotation)
	auto siny_cosp = 2 * (q.w * q.z + q.x * q.y);
	auto cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
	angles.yaw = std::atan2(siny_cosp, cosy_cosp);

	return angles;
}	

//Convert this eulerangle to quaternion
inline Quaternion fromEulerToQuaternion(EulerAngles &e)
{
	Quaternion q;

	auto cy = cos(e.yaw * 0.5);
	auto sy = sin(e.yaw * 0.5);
	auto cp = cos(e.pitch * 0.5);
	auto sp = sin(e.pitch * 0.5);
	auto cr = cos(e.roll * 0.5);
	auto sr = sin(e.roll * 0.5);

	q.w = cr * cp * cy + sr * sp * sy;
	q.x = sr * cp * cy - cr * sp * sy;
	q.y = cr * sp * cy + sr * cp * sy;
	q.z = cr * cp * sy - sr * sp * cy;


	return q;
}
