#pragma once
#include "Component.h"
#include <glew.h>
#include <SDL_image.h>

class MaterialComponent: public Component {
	public:
		MaterialComponent(Component* parent_, const char* filename_);
		virtual ~MaterialComponent();
		virtual bool OnCreate();
		virtual void OnDestroy();
		virtual void Update(const float deltaTime_);
		virtual void Render()const;
		inline GLuint getTextureID() const { return textureID; }


private:
	GLuint textureID;
	const char* filename;

};

