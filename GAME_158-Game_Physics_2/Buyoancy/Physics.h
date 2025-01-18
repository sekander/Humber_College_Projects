#ifndef PHYSICS_H
#define PHYSICS_H

#include <iostream>
#include <math.h>
#include "nahid_math.h"

/*
 * Nahid Sekander
 * n01001831
 * 03/09/22
 * */


struct edge
{
	vec_3 start;
	vec_3 end;

};

struct bounding_box
{
	vec_3 origin;
	vec_3 bottom_right;
	vec_3 top_right;
	vec_3 top_left;
};

class Physics
{
    public:

	Physics(){};
	
        Physics(vec_3 position, vec_3 velocity, vec_3 acceleration, vec_3 force,
        long torque, long mass ,double angle, double angularVelocity, double angularAcceleration, 
	double rotational_inertia)
        {
            position = position;
            velocity = velocity;
            acceleration = acceleration;
            force = force;
            torque = torque;
            mass = mass;
            angle = angle;
            angularVelocity = angularVelocity;
            angularAcceleration = angularAcceleration;
	    rotational_inertia = rotational_inertia;
        }

        ~Physics(){};


	//Calculate Position based on given velocity and acceleration
        void calculatePosition(vec_3 &position, vec_3 &velocity, vec_3 &acceleration, int time)
        {
            position.x += velocity.x*time + (acceleration.x/2) * (time*time);
            position.y += velocity.y*time + (acceleration.y/2) * (time*time);
            setPosition(position.x,position.y);

        }

	//Calculate Linear Velocity of Physic object
        void calculateVelocity(vec_3 &velocity, vec_3 &acceleration, int time)
        {
            velocity.x += acceleration.x*time;
            velocity.y += acceleration.y*time;
            setVelocity(velocity.x, velocity.y);

        }

	//Calculate Linear Acceleration of Physic object
        void calculateAcceleration(vec_3 &force, int mass)
        {
            acceleration.x = force.x/mass;
            acceleration.y = force.y/mass;
        }

	//Calcualate angle displacment of Physic object
        void calculateAngle(float angularVelocity, float angularAcceleration, int time)
        {
            angle += angularVelocity*time + (angularAcceleration/2) * (time*time);
        }

	//Calculate angular velocity of Physic object
        void calculateAngularVelocity(float angularAcceleration, int time)
        {
            angularVelocity += angularAcceleration*time;
        }

	//Calculate angular acceleration of Physic object
	void calculateAngularAcceleration(){
		angularAcceleration = torque / rotational_inertia;
		//angularAcceleration = torque / mass;
	}

	//Calculate force thrust acted up Physic object 
        void calculateForce(vec_3 force, float theta)
        {
            force.x = (force.x * cos(theta)) - (force.y * sin(theta));
            force.y = (force.x * sin(theta)) + (force.y * cos(theta));

            setForce(force.x, force.y);
        }

	//Set Position, Velocity, and Force of the Physic object
        void setPosition(float x, float y){ position.x = x; position.y = y;}
        void setVelocity(float x, float y){ velocity.x = x; velocity.y = y;}
        void setForce(float x, float y){ force.x = x; force.y = y;}


	//Public Member variables 
        vec_3 position;
        vec_3 velocity;
        vec_3 acceleration;
        vec_3 force;
        
	//int mass;
	long mass;
        //int torque;
        long torque;
	//int rotational_inertia;
	double rotational_inertia;
        
	
	//float angularAcceleration;
	double angularAcceleration;
        //float angle;
        double angle;
        //float angularVelocity;
        double angularVelocity;

	float radius;

    protected:







};

	inline static int checkRay_Sphere(Physics& p, ray& r)
	{

		Sphere s;
		s.position = p.position;
		s.radius = p.radius;
	
		std::cout << s.position.x << " : " << s.position.y << " : "  << s.radius <<std::endl;
		r.start.print_vec();
		r.dir.print_vec();
		return RaySphereCollisionDetected(r,s);


		/*
		auto a = r.start - p.position;	
		auto b = dot(r.dir, a);
		auto c = dot(a, a) - (p.radius*p.radius);

		auto d = (b * b) - c;
		
		return d;
		if(d < 0)
			return false;
		if(d > 0)
			return true;
		*/

	}
	

	//Roof to phsyics object collison
	inline static void checkRoofCollision(Physics &p, ray &e)
	//inline static void checkRoofCollision(Physics &p, edge &e)
	{
		if(p.position.x < e.start.x &&
		   p.position.y < e.start.y ||
		   p.position.x > e.dir.x &&
		   p.position.y < e.dir.y)
		p.velocity = p.velocity;	
		else if(p.position.y < e.start.y &&
			p.position.y < e.dir.y)
		{
		
			std::cout << "MADE CONTACT" << std::endl;		
			std::cout << "#################################################" << std::endl;

			//p.position.x = e.start.x;
			p.velocity.y = -p.velocity.y;
		}
	}


	//Wall to physic object collison
	inline static void checkLeftWallCollision(Physics &p, ray& e)
	{
		if((p.position.x < e.start.x  &&
		    p.position.y < e.start.y) ||
		   (p.position.x < e.dir.x &&
		    p.position.y > e.dir.y))
		{
			p.velocity = p.velocity;		
		}
		else if(p.position.x < e.start.x &&
		   p.position.x < e.dir.x){
			std::cout << "MADE CONTACT" << std::endl;		
			std::cout << "#################################################" << std::endl;

			//p.position.x = e.start.x;
			p.velocity.x = -p.velocity.x;
			//p.velocity.y = 0;
			//p.force.x = 0;
		}

	}

	//Roof to phsyics object collison
	inline static void checkFloorCollision(Physics &p, ray &e)
	//inline static void checkRoofCollision(Physics &p, edge &e)
	{
		if(p.position.x > e.start.x &&
		   p.position.y < e.start.y - (2*p.radius)||
		   p.position.x > e.dir.x &&
		   p.position.y < e.dir.y - (2*p.radius))
		p.velocity = p.velocity;	
		else if(p.position.y  > (e.start.y - (2*p.radius)) &&
			p.position.y  > (e.dir.y - (2*p.radius)))
		//else if(p.position.y  > (e.start.y - 100) &&
		//	p.position.y  > (e.dir.y - 100))
		{
		
			std::cout << "MADE CONTACT" << std::endl;		
			std::cout << "#################################################" << std::endl;

			//p.position.x = e.start.x;
			p.velocity.y = -p.velocity.y;
		}
	}


	//Wall to physic object collison
	inline static void checkRightWallCollision(Physics &p, ray& e)
	{
		if((p.position.x < e.start.x - (2*p.radius)  &&
		    p.position.y > e.start.y) ||
		   (p.position.x < e.dir.x - (2*p.radius) &&
		    p.position.y > e.dir.y))
		{
			p.velocity = p.velocity;		
		}
		else if(p.position.x > e.start.x - (2*p.radius) &&
		   p.position.x > e.dir.x- (2*p.radius)){
			std::cout << "MADE CONTACT" << std::endl;		
			std::cout << "#################################################" << std::endl;

			//p.position.x = e.start.x;
			p.velocity.x = -p.velocity.x;
			//p.velocity.y = 0;
			//p.force.x = 0;
		}

	}
	//Sphere collision Detection 
	//Check if collision occured
	inline static bool SphereSphereCollisionDetected(const Physics &p1, const Physics &p2)
	{
		//Future coding in here
		return false;
	}

	inline static bool SpherePlaneCollisionDetected(const Physics &p, const plane &plane)
	{
		//Future coding in here
		return false;
	}

	//Calculate Collison Here
	inline static void SphereSphereCollisionResponse(Physics &p1, Physics &p2, float e)
	{

		//Future coding in here
	
			
		//First Sphere
		auto s11 = vec_3(p1.mass*p1.velocity.x, p1.mass*p1.velocity.y, p1.mass*p1.velocity.z);
		auto s12 = vec_3(p2.mass*p2.velocity.x, p2.mass*p2.velocity.y, p2.mass*p2.velocity.z);
		auto s13 = vec_3(p1.mass*e*p1.velocity.x, p1.mass*e*p1.velocity.y, p1.mass*e*p1.velocity.z);
		auto s14 = vec_3(p1.mass*e*p2.velocity.x, p1.mass*e*p2.velocity.y, p1.mass*e*p2.velocity.z);
		//auto vf1 = (s11 + s12);
		auto vf1 = (s11 + s12 + s13 - s14);
		vf1 = vec_3( vf1.x/(p1.mass + p2.mass),  vf1.y/(p1.mass + p2.mass),  vf1.z/(p1.mass + p2.mass));


		//Second Sphere
		//
		auto s21 = vec_3(p2.mass*p2.velocity.x, p2.mass*p2.velocity.y, p2.mass*p2.velocity.z);
		auto s22 = vec_3(p1.mass*p1.velocity.x, p1.mass*p1.velocity.y, p1.mass*p1.velocity.z);
		auto s23 = vec_3(p2.mass*e*p2.velocity.x, p2.mass*e*p2.velocity.y, p2.mass*e*p2.velocity.z);
		auto s24 = vec_3(p2.mass*e*p1.velocity.x, p2.mass*e*p1.velocity.y, p2.mass*e*p1.velocity.z);
		//auto vf2 = (s21 + s22);
		auto vf2 = (s21 + s22 + s23 - s24);
		vf2 = vec_3( vf2.x/(p1.mass + p2.mass),  vf2.y/(p1.mass + p2.mass),  vf2.z/(p1.mass + p2.mass));

		p1.velocity = vf2;
		p2.velocity = vf1;

	}

	inline static void SphereStaticSphereCollisionResponse(Physics &p1, const Physics &static_p)
	{
		//Future coding in here
		//
		//

		//Find the normal vector
		//
		auto n = p1.position - static_p.position;

		//Normalize the normal
		//
		auto r = sqrt((n.x*n.x) + (n.y*n.y) + (n.z*n.z));

		auto n_n = vec_3((n.x/r), (n.y/r), (n.z/r));

		//Find the dot product of -vi and normalize normal
		auto vi = p1.velocity * -1;
		
		auto pm = dot(vi, n_n);

		auto p = vec_3((pm*n_n.x), (pm*n_n.y),(pm*n_n.z));

		//Find the final velocity
		auto vf = vec_3((p1.velocity.x + (2 * p.x)), (p1.velocity.y + (2 * p.y)), (p1.velocity.z + (2 * p.z)));
		p1.velocity = vf;
	}

	//inline static void SpherePlaneCollisionResponse(Physics &p1, const plane &plane)
	inline static void SpherePlaneCollisionResponse(Physics &p1, const ray &plane)
	{
		//Future coding in here
		//
		//
		
		//Reverse p1 velocity
		auto vi = p1.velocity * -1;

		auto nu_n = vec_3(plane.dir.x - plane.start.x, plane.dir.y - plane.start.y, plane.dir.z - plane.start.z);


		//Normalize the normal of the plane
		auto r = sqrt((nu_n.x*nu_n.x) + (nu_n.y*nu_n.y) + (nu_n.z*nu_n.z));
		//auto r = sqrt((plane.x*plane.x) + (plane.y*plane.y) + (plane.z*plane.z));
		auto n_n = vec_3((nu_n.x/r), (nu_n.y/r), (nu_n.z/r));
		//auto n_n = vec_3((plane.x/r), (plane.y/r), (plane.z/r));

		//Find the dot product of -vi and normalize normal
		auto pm = dot(vi, n_n);

		//Multiply pm by the normal vector to find projection vector
		//
		auto p = vec_3((pm*n_n.x),(pm*n_n.y),(pm*n_n.z));

		//Find the final velocity
		//
		auto vf = vec_3((p1.velocity.x + (2 * p.x)), (p1.velocity.y + (2 * p.y)), (p1.velocity.z + (2 * p.z)));

		p1.velocity = vf;

	}






#endif // PHYSICS_H
