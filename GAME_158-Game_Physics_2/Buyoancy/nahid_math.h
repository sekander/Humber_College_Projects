/*
 * Nahid Sekander
 * n01001831
 * GAME 156
 * Assignment #2
 * */


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


	vec_3(float x_pos, float y_pos, float z_pos = 0)
	{
		x = x_pos;
		y = y_pos;
		z = z_pos;
	}


//	Vector scalar multiplication

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

inline static bool SphereSphereCollisionDetected(const Sphere& a, const Sphere& b)
{
	vec_3 d = a.position - b.position;
       	float length = dot(d, d);

	// sum of radius
	//
	float sum = a.radius + b.radius;

	if(length <= sum)
		return true;

	return false;	
}

inline static bool SpherPlaneCollisionDetected(const Sphere& a, const plane& p)
{
	auto s = p.x * a.position.x;
	auto r = p.y * a.position.y;
	auto e = p.z * a.position.z;

	auto d = s + r + e;

	if(d <= a.radius)
		return true;
	

	return false;
}


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
inline static std::vector<plane> checkRaywihBB(ray &r, AAB &b)
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

/*
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
*/
