#include "Box.h"

#include "MMath.h"
#include "Matrix.h"

using namespace MATH;
using namespace GEOMETRY;

/*
  F/----------/E
  /	|		 / |
 /	|		/  |
B|----------|A |
 |	|	    |  |
 |  H|______|__|G
 |  /	    |  /
 | /		| /
 |/_________|/
 D			C
*/


void Box::generateVerticesAndNormals()
{

	Vec3 A = Vec3(centre.x + halfExtents.x, centre.y + halfExtents.y, centre.z + halfExtents.z);
	Vec3 B = Vec3(centre.x - halfExtents.x, centre.y + halfExtents.y, centre.z + halfExtents.z);
	Vec3 C = Vec3(centre.x + halfExtents.x, centre.y - halfExtents.y, centre.z + halfExtents.z);
	Vec3 D = Vec3(centre.x - halfExtents.x, centre.y - halfExtents.y, centre.z + halfExtents.z);
	Vec3 E = Vec3(centre.x + halfExtents.x, centre.y + halfExtents.y, centre.z - halfExtents.z);
	Vec3 F = Vec3(centre.x - halfExtents.x, centre.y + halfExtents.y, centre.z - halfExtents.z);
	Vec3 G = Vec3(centre.x + halfExtents.x, centre.y - halfExtents.y, centre.z - halfExtents.z);
	Vec3 H = Vec3(centre.x - halfExtents.x, centre.y - halfExtents.y, centre.z - halfExtents.z);


	//Front
	//Triangle 1
	vertices.push_back(orientation * A);
	normals.push_back(A);
	vertices.push_back(orientation * B);
	normals.push_back(B);
	vertices.push_back(orientation * C);
	normals.push_back(C);

	//Triangle 2
	vertices.push_back(orientation * B);
	normals.push_back(B);
	vertices.push_back(orientation * C);
	normals.push_back(C);
	vertices.push_back(orientation * D);
	normals.push_back(D);

	//Top
	//Triangle 4
	vertices.push_back(orientation * A);
	normals.push_back(A);
	vertices.push_back(orientation * B);
	normals.push_back(B);
	vertices.push_back(orientation * E);
	normals.push_back(E);

	vertices.push_back(orientation * B);
	normals.push_back(B);
	vertices.push_back(orientation * F);
	normals.push_back(F);
	vertices.push_back(orientation * E);
	normals.push_back(E);


	//Left
	vertices.push_back(orientation * D);
	normals.push_back(D);
	vertices.push_back(orientation * B);
	normals.push_back(B);
	vertices.push_back(orientation * F);
	normals.push_back(F);

	vertices.push_back(orientation * D);
	normals.push_back(D);
	vertices.push_back(orientation * H);
	normals.push_back(H);
	vertices.push_back(orientation * F);
	normals.push_back(F);

	//Right
	//Triangle 3
	vertices.push_back(orientation * A);
	normals.push_back(A);
	vertices.push_back(orientation * G);
	normals.push_back(G);
	vertices.push_back(orientation * E);
	normals.push_back(E);

	vertices.push_back(orientation * A);
	normals.push_back(A);
	vertices.push_back(orientation * C);
	normals.push_back(C);
	vertices.push_back(orientation * G);
	normals.push_back(G);


	//Bottom
	vertices.push_back(orientation * D);
	normals.push_back(D);
	vertices.push_back(orientation * H);
	normals.push_back(H);
	vertices.push_back(orientation * G);
	normals.push_back(G);

	vertices.push_back(orientation * D);
	normals.push_back(D);
	vertices.push_back(orientation * C);
	normals.push_back(C);
	vertices.push_back(orientation * G);
	normals.push_back(G);



	//Back
	vertices.push_back(orientation* H);
	normals.push_back(H);
	vertices.push_back(orientation* F);
	normals.push_back(F);
	vertices.push_back(orientation* E);
	normals.push_back(E);

	vertices.push_back(orientation* H);
	normals.push_back(H);
	vertices.push_back(orientation* C);
	normals.push_back(C);
	vertices.push_back(orientation* E);
	normals.push_back(E);


}