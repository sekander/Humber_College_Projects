#pragma once
#include "Shape.h"
#include "Vector.h"
#include "Quaternion.h"
#include <vector>
namespace GEOMETRY {
	struct Box : public MATH::Vec3, public Shape {
		MATH::Vec3 centre;
		MATH::Vec3 halfExtents;
		MATH::Quaternion orientation;

		Box() = default;
		
		Box(MATH::Vec3 centre_, MATH::Vec3 halfExtents_, MATH::Quaternion orientation_) {
			set(centre_, halfExtents_, orientation_);

			std::cout << "Box\n" 
				<< "\nCentre A :: \nx = " << centre.x
				<< "\ny = " << centre.y
				<< "\nz = " << centre.z
				//<< "\nsphereCentre B :: \nx = " << sphereCentrePosB.x
				//<< "\ny = " << sphereCentrePosB.y
				//<< "\nz = " << sphereCentrePosB.z <<
				<< std::endl;
		}

		void set(MATH::Vec3 centre_, MATH::Vec3 halfExtents_, MATH::Quaternion orientation_) {
			centre = centre_;
			halfExtents = halfExtents_;
			orientation = orientation_;

			//TODO
			generateVerticesAndNormals();
			StoreMeshData(GL_TRIANGLES);



		}


		void generateVerticesAndNormals() override;
		//void rayIntersectionInfo(const Ray& ray) const ;
		void test(const float ray) const override{}

	};

}