#pragma once
#include <glew.h>
#include "Actor.h"
#include "Vector.h"
using namespace MATH;

enum class LightStyle {
	DirectionLight = 1,
	PointLight,
	SkyLight,
	SpotLight
};

class LightActor : public Actor {
private:
	LightStyle lightStyle;
	Vec3 position;
	Vec4 colour;
	float intensity;
	Vec3 fallOff;
	GLuint uboLightDataID;
	const GLuint bindPoint = 1;

public:
	LightActor(Component* parent_, LightStyle lightStyle_, Vec3 location_, Vec4  colour_,
		float intensity = 1.0f, Vec3 fallOff = Vec3(0.0f, 0.0f, 0.0f));
	~LightActor();
	Vec3 GetPosition() const { return position; }
	void SetPosition(Vec3 _position) { position = _position; }
	Vec4 GetColour() const { return colour; }
	void SetColour(Vec4 _colour) { colour = _colour; }
	bool OnCreate() override;
	void OnDestroy() override;
	GLuint GetLightID() { return uboLightDataID; }



};

