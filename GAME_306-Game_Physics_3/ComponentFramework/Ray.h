#pragma once

#include "Shape.h"
#include "Vector.h"
//#include "Quaternion.h"
#include <vector>
namespace GEOMETRY {
	struct Ray : public MATH::Vec3, public Shape {
		MATH::Vec3 starting_point;
		MATH::Vec3 direction;


		Ray(MATH::Vec3 starting_point_, MATH::Vec3 direction_)
		{
			starting_point = starting_point_;
			direction = direction_;
		}

		void generateVerticesAndNormals() override {}

		void rayIntersectionInfo(const Ray& ray) const ;
		void test(const float ray) const override{}

	};
}