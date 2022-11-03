#pragma once
#include "Shape.h"
#include "Vector.h"
#include <vector>
namespace GEOMETRY {
	struct Capsule : public MATH::Vec3, public Shape {
		float r = 1.0f;
		MATH::Vec3 sphereCentrePosA;
		MATH::Vec3 sphereCentrePosB;

		Capsule() = default;

		Capsule(float r_, MATH::Vec3 sphereCentrePosA_, MATH::Vec3 sphereCentrePosB_){
			set(r_, sphereCentrePosA_, sphereCentrePosB_);

			std::cout << "Capusle\n" << "radius : " << r
				<< "\nsphereCentre A :: \nx = " << sphereCentrePosA.x
				<< "\ny = " << sphereCentrePosA.y
				<< "\nz = " << sphereCentrePosA.z
				<< "\nsphereCentre B :: \nx = " << sphereCentrePosB.x
				<< "\ny = " << sphereCentrePosB.y
				<< "\nz = " << sphereCentrePosB.z << 
			std::endl;
		}

		void set(float r_, MATH::Vec3 sphereCentrePosA_, MATH::Vec3 sphereCentrePosB_) {
			r = r_;
			sphereCentrePosA = sphereCentrePosA_;
			sphereCentrePosB = sphereCentrePosB_;

			//TODO
			generateVerticesAndNormals();
			StoreMeshData(GL_POINTS);


		}


		void generateVerticesAndNormals() override;

		//void rayIntersectionInfo(const Ray& ray) const ;
		void test(const float ray) const override{}

	};

}