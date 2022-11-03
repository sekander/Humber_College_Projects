#include <iostream>
#include "nahid_math.h"

using std::cout;
using std::endl;
int main (){

	{
	auto e = 0.8;

	vec_3 a(4.28, -8.01);	
	a.print_vec();
	vec_3 b(0.31, 0.35);
	b.print_vec();
	vec_3 av(0.05, 6.97);

	auto ba = b - a;
	ba.print_vec();

	auto nba = normalize(ba);
	nba.print_vec();

	auto p = nba * dot((av * -1), nba);
	p.print_vec();

	auto vf = av + (p * 2);	
	vf.print_vec();
	auto m = magnitude(vf);
	m = m * e;	
	cout << m;
	}

	{
	vec_3 vi(-30,-40);	
	vi.print_vec();
	vec_3 n(-0.6, 0.8);
	n.print_vec();
	auto p = n * (dot(vi * -1, n));
	p.print_vec();
	auto vf = vi + (p * 2);
	vf.print_vec();	

	}	
	

return 0;
}
