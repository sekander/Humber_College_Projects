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
return 0;
}
