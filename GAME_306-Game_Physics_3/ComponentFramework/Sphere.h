/// Umer Noor 2022
/// Originally written by Dr. Scott Fielder
/// Part of his MATH library. I moved it to GEOMETRY and inherited from Shape

#ifndef SPHERE_H
#define SPHERE_H
#include "Shape.h"
#include "Vector.h"
#include <vector>
#include "Ray.h"
#include "VMath.h"

namespace GEOMETRY {
	struct Sphere : public MATH::Vec3, public Shape {
		float r = 1.0f;
		/// Just a little utility to populate a Sphere. The position of the centre of the sphere is the Vec3 inherited
		inline void set(float x_, float y_, float z_, float r_) {
			x = x_; y = y_; z = z_;
			r = r_;

			generateVerticesAndNormals();
			StoreMeshData(GL_POINTS);
		}

		Sphere() = default;

		Sphere(float x, float y, float z, float r) {
			set(x, y, z, r);
		}

		Sphere(MATH::Vec3 centre, float r) {
			set(centre.x, centre.y, centre.z, r);
		}

		Sphere(const Sphere& s) {
			set(s.x, s.y, s.z, s.r);
		}

		/// print the values of the sphere and add a comment if you wish
		void print(const char* comment = nullptr) {
			if (comment) printf("%s\n", comment);
			printf("%f %f %f %f\n", x, y, z, r);
		}

		void generateVerticesAndNormals() override;


		// RayIntersectionInfo rayIntersectionInfo(const Ray& ray) const override; (TO DO)
		void rayIntersectionInfo(const Ray& ray) const 
		{
			/*
			auto a = VMath::dot(ray.direction, ray.direction);
			auto b = 2 * (VMath::dot(ray.starting_point, ray.direction));
			auto c = (VMath::dot(ray.starting_point, ray.starting_point) - (r * r));

			auto d = b * b - 4 * (a * c);

			if (d < 0)
				std::cout << "False" << std::endl;
			else if(d > 0)
				std::cout << "True" << std::endl;
			*/

		}

		void test(const float ray) const override{}






	};
}
#endif