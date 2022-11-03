#include "ShapeComponent.h"

ShapeComponent::ShapeComponent(Component* parent_, GEOMETRY::Sphere sphere_) :Component(parent_)
{
	shapeType = ShapeType::sphere;
	shape = std::make_shared<GEOMETRY::Sphere>(MATH::Vec3(sphere_.x, sphere_.y, sphere_.z), sphere_.r);

	
}

ShapeComponent::ShapeComponent(Component* parent_, GEOMETRY::Cylinder cylinder_) :Component(parent_)
{
	shapeType = ShapeType::cylinder;
	shape = std::make_shared<GEOMETRY::Cylinder>(cylinder_.r, cylinder_.capCentrePosA, cylinder_.capCentrePosB);


}

ShapeComponent::ShapeComponent(Component* parent_, GEOMETRY::Capsule capsule) :Component(parent_)
{
	shapeType = ShapeType::capsule;
	shape = std::make_shared<GEOMETRY::Capsule>(capsule.r, capsule.sphereCentrePosA, capsule.sphereCentrePosB);
}

ShapeComponent::ShapeComponent(Component* parent_, GEOMETRY::Box box) :Component(parent_)
{
	shapeType = ShapeType::box;
	shape = std::make_shared<GEOMETRY::Box>(box.centre, box.halfExtents, box.orientation);
}

ShapeComponent::ShapeComponent(Component* parent_, GEOMETRY::Ray ray) :Component(parent_)
{
	shapeType = ShapeType::ray;
	shape = std::make_shared<GEOMETRY::Ray>(ray.starting_point, ray.direction);
}

ShapeComponent::~ShapeComponent()
{
}

bool ShapeComponent::OnCreate()
{
	return true;
}

void ShapeComponent::OnDestroy()
{
}

void ShapeComponent::Update(const float deltaTime_)
{
}

void ShapeComponent::Render() const
{
	shape->debugDraw();
}

//Create new draw method
