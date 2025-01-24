#include "Cylinder.h"
#include "MMath.h"
#include "Matrix.h"

using namespace MATH;
using namespace GEOMETRY;



void Cylinder::generateVerticesAndNormals()
{
	const float deltaTheta = 1.0f;
	const float deltaPhi = 360.0f / 15.0f;
	Vec3 V = capCentrePosB - capCentrePosA;

	auto cylinderLength = VMath::mag(V);

	auto axis = VMath::normalize(V);
	auto nudgeAxis = axis + Vec3(1.0f, 1.0f, 1.0f);
	auto radialVector = r * VMath::normalize(VMath::cross(axis, nudgeAxis));



	

	for (float thetaDeg = 0.0f; thetaDeg <= 360.0f; thetaDeg += deltaTheta)
	{
		
		for (float stepsAlongAxis = 0; stepsAlongAxis < cylinderLength; stepsAlongAxis += 0.1f)
		{
			Vec3 circle = capCentrePosA + radialVector + axis * stepsAlongAxis;
			Matrix3 rotationMatrix = MATH::MMath::rotate(thetaDeg, axis);
			circle = rotationMatrix * circle;

			vertices.push_back(circle);
			normals.push_back(circle);
		}
		

	
			for (float i = 0.0f; i < r; i+=0.25f)
			{
				Vec3 circle((r - i) * sin(thetaDeg * DEGREES_TO_RADIANS), (r - i) * cos(thetaDeg * DEGREES_TO_RADIANS), 0.0f);
				MATH::Matrix3 rotationMatrix;
				rotationMatrix = MATH::MMath::rotate(deltaPhi, Vec3(0.0f, 1.0f, 0.0f));
				circle = rotationMatrix * circle;
				vertices.push_back(circle);
				normals.push_back(circle - Vec3(x, y, z));
			}



		}
	


	
}