#include "MaterialComponent.h"

MaterialComponent::MaterialComponent(Component* parent_, const char* filename_):Component(parent_) {
	filename = filename_;
}
MaterialComponent::~MaterialComponent() {
	OnDestroy();
}

bool MaterialComponent::OnCreate() {
	if (isCreated) return true;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	SDL_Surface* textureSurface = IMG_Load(filename);
	if (textureSurface == nullptr) {
		return false;
	}
	int mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	//Data transfering to gpu
	glTexImage2D(GL_TEXTURE_2D, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	//free cpu memory
	SDL_FreeSurface(textureSurface);
	/// Wrapping and filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0); /// Unbind the texture
	
	isCreated = true;
	return isCreated;
}


void MaterialComponent::OnDestroy() {
	glDeleteTextures(1, &textureID);
	isCreated = false;
}
void MaterialComponent::Update(const float deltaTime) {}
void MaterialComponent::Render()const {}
