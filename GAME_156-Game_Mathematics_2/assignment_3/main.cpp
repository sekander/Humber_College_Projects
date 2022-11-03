#include <iostream>
#include "nahid_math.h"

using std::cout;
int main (){

	cout << "Linear Alegebgra : GAME Mathematics 2\n";
	cout << "#####################################\n";
	cout << "Vec 3\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";

	//vec_3 v(2, 2, 1);
	//vec_3 u(4, 2, 1);
	vec_3 v{2, 2, 1};
	vec_3 u{4, 2, 1};
 	vec_3 origin{};


	cout << "Default Vector O is : ";
	origin.print_vec();
	cout << "Vector V is : ";
	v.print_vec();
	auto n_v = normalize(v);

	cout << "Vector U is : ";
	u.print_vec();

	cout << "Magnitude of V is : " << magnitude(v) << "\n";
	cout << "Normalized V is : ";
	n_v.print_vec();

	auto scalar = dot(v, u);
	cout << "Dot product V.U is : " << scalar << "\n"; 

	cout << "Cross product U V is : ";
	cross(u, v).print_vec();

	cout << "Cross product V U is : ";
	cross(v, u).print_vec();

	cout << "#####################################\n";
	cout << "Vec 4\n";
	vec_4 z(2, 2, 1, 3);
	vec_4 x(4, 2, 1, 3);
	vec_4 t = vec_4();

	cout << "Vector T is : ";
	t.print_vec();

	cout << "Vector Z is : ";
	z.print_vec();
	auto n_z = z.normalize(z);

	cout << "Vector X is : ";
	x.print_vec();

	cout << "Magnitude of Z is : " << z.magnitude(z) << "\n";
	cout << "Normalized Z is : ";
	n_z.print_vec();

	auto vec_4_scalar = z.dot(z, x);
	cout << "Dot product Z.X is : " << vec_4_scalar << "\n"; 
	
	ray ray_1(vec_3(1, 0, 1), vec_3(3, 2, 1));
	ray_1.current_position(5).print_vec(); 

	Point3D p(1, 0, 1);
	vec_3   vv(3, 2, 1);

	plane pp(2, 1, 0, -4);

	cout << "\n\nAssignment 2\n";
	cout << "-------------\n";
	cout << "\nIntersection with Line :\n";
        p.print_vec();	
	vv.print_vec();
	cout << "and ";
	pp.print_plane();
	
	cout << "Intersection :\n";

	ray r(vec_3(1, 0, 1), vec_3(3, 2, 1));
	intersection_ray_plane(r, pp).print_vec();


	cout << "\n\nAssignment 3\n";
	cout << "----------------\n\n";


	cout << "Part 1\n";
	cout << "------------------------------------\n";


	ray r_s(vec_3(2, -1, -1), vec_3(0, 2, 3));

	cout << "Ray\n";
	cout << "Start Position : "; r_s.start.print_vec();
	cout << "Direction Vector : "; r_s.dir.print_vec();

	Sphere sphere(vec_3(0,0,0), 5);
	cout << "\nSphere\n";
	cout << "Origin Position : "; sphere.position.print_vec();
	cout << "Radius : " << sphere.radius << "\n";	

	if(RaySphereCollisionDetected(r_s, sphere)){
		cout << "\nCollided\n";
		RaySphereCollisionPoint(r_s, sphere, 1).print_vec();
		RaySphereCollisionPoint(r_s, sphere, 2).print_vec();
	}
	else
		cout << "\nMiss\n";

	cout << "\nPart 2\n";
	cout << "------------------------------------\n";

//	plane p0(1,0,0,0);
//	plane p1(0,1,0,0);
//	plane p2(0,0,1,0);
//	plane p3(1,0,0,1);
//	plane p4(0,1,0,1);
//	plane p5(0,0,1,1);

	//AAB box(p0,p1,p2,p3,p4,p5);

	AAB box(1, 1, 1);


	cout << "Ray\n";
	cout << "Start Position : "; r_s.start.print_vec();
	cout << "Direction Vector : "; r_s.dir.print_vec();


	cout << "\nBox\n";
	for(auto s : box.box)
		s.print_plane();

	auto checks = checkRaywihBB(r_s, box);

	//Loop through all planes that intersects with ray, then find intersection point
	for(auto iter : checks){
		cout << "\nChecking which planes interesect with ray\n";
		iter.print_plane();	
	
		cout << "\nIntersection : ";
		intersection_ray_plane(r_s, iter).print_vec();
	}

	//Code that doesnt work properly
	/*
	cout << "\nTESTING \n";
	cout << "Ray\n";

	ray nu_ray(vec_3(2, -1, -1), vec_3(0, 2, 3));
	cout << "Start Position : "; nu_ray.start.print_vec();
	cout << "Direction Vector : "; nu_ray.dir.print_vec();


	cout << "\nBox\n";
	for(auto s : box.box)
		s.print_plane();


	auto bu_checks = sscheckRaywihBB(nu_ray, box);

	cout << "\nSize of checks " << bu_checks.size() << std::endl;

	for(auto iter : bu_checks){
		cout << "\nChecking which planes interesect with ray\n";
		iter.print_plane();
		cout << "\nIntersection : ";
		intersection_ray_plane(nu_ray, iter).print_vec();
	}	
	*/
return 0;
}
