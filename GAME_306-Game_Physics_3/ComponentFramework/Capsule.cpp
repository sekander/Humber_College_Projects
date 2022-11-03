#include "Capsule.h"
#include "MMath.h"
#include "Matrix.h"

using namespace MATH;
using namespace GEOMETRY;

void Capsule::generateVerticesAndNormals()
{

	const float deltaTheta = 1.0f;
	const float deltaPhi = 360.0f / 15.0f;
	const float deltaPhiH = 180.0f / 15.0f;

	Vec3 V = sphereCentrePosB - sphereCentrePosA;

	auto cylinderLength = VMath::mag(V);

	auto axis = VMath::normalize(V);
	auto nudgeAxis = axis + Vec3(1.0f, 1.0f, 1.0f);
	auto radialVector = r * VMath::normalize(VMath::cross(axis, nudgeAxis));

	//This Loop draws the capsule sides using cylinder logic
	for (float thetaDeg = 0.0f; thetaDeg <= 360.0f; thetaDeg += deltaTheta)
	{

		for (float stepsAlongAxis = 0; stepsAlongAxis < cylinderLength; stepsAlongAxis += 0.1f)
		{
			Vec3 circle = sphereCentrePosA + radialVector + axis * stepsAlongAxis;
			Matrix3 rotationMatrix = MATH::MMath::rotate(thetaDeg, axis);
			circle = rotationMatrix * circle;

			vertices.push_back(circle);
			normals.push_back(circle);
		}
	}

	//Calculates vertices for top and bottom hemisphere
	//Use only one pie to do 1 - 180 degrees angle 
	//Start at 90 degrees and to 270 

	for(float thetaDegree = 90.0f; thetaDegree <= 270.0f; thetaDegree += deltaTheta)
	{
		Vec3 circle(r * sin(thetaDegree * DEGREES_TO_RADIANS), r * cos(thetaDegree * DEGREES_TO_RADIANS), 0.0f);
		Vec3 topCircle = sphereCentrePosB + circle;
		Vec3 bottomCircle = sphereCentrePosA - circle;

		for(float degree = 90.0f; degree <= 270.0f; degree += deltaPhi) {
			MATH::Matrix3 rotationMatrix;
			rotationMatrix = MATH::MMath::rotate(deltaPhiH, Vec3(0.0f, 1.0f, 0.0f));

			topCircle = rotationMatrix * topCircle;
			bottomCircle = rotationMatrix * bottomCircle;


			vertices.push_back(topCircle);
			normals.push_back(topCircle - Vec3(0.0f, 1.0f, 0.0f));

			vertices.push_back(bottomCircle);
			normals.push_back(bottomCircle - Vec3(0.0f, 1.0f, 0.0f));
		}
	}
	
}