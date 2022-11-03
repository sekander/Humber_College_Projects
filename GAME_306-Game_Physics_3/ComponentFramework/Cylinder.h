#pragma once
#include "Shape.h"
#include "Vector.h"
#include <vector>
namespace GEOMETRY {
	struct Cylinder : public MATH::Vec3, public Shape {
		float r = 1.0f;
		MATH::Vec3 capCentrePosA;
		MATH::Vec3 capCentrePosB;
		/// Just a little utility to populate a Sphere. The position of the centre of the sphere is the Vec3 inherited
		inline void set(float r_, MATH::Vec3 capCentrePosA_, MATH::Vec3 capCentrePosB_) {
		
			r = r_;
			capCentrePosA = capCentrePosA_;
			capCentrePosB = capCentrePosB_;

	
			

			generateVerticesAndNormals();
			StoreMeshData(GL_POINTS);
		}

		Cylinder() = default;

		Cylinder(float r_, MATH::Vec3 capCentrePosA_, MATH::Vec3 capCentrePosB_) {
			set(r_, capCentrePosA_, capCentrePosB_);

			std::cout << "Cylinder\n" << "radius : " << r
				<< "\nsphereCentre A :: \nx = " << capCentrePosA.x
				<< "\ny = " << capCentrePosA.y
				<< "\nz = " << capCentrePosA.z
				<< "\nsphereCentre B :: \nx = " << capCentrePosB.x
				<< "\ny = " << capCentrePosB.y
				<< "\nz = " << capCentrePosB.z <<
			std::endl;
		}


		/// print the values of the sphere and add a comment if you wish
		void print(const char* comment = nullptr) {
			//if (comment) printf("%s\n", comment);
			//printf("%f %f %f %f\n", x, y, z, r);
		}

		// RayIntersectionInfo rayIntersectionInfo(const Ray& ray) const override; (TO DO)
		void generateVerticesAndNormals() override;

		//void rayIntersectionInfo(const Ray& ray) const ;
		void test(const float ray) const override{}

	};

	
	
	
}