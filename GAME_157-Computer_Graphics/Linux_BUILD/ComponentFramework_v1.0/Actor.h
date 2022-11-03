#pragma once
#include <iostream>
#include <vector> 
#include "Component.h"
#include "Matrix.h"
using namespace MATH;

class Actor: public Component {
private:
	std::vector<Component*> components;
	Matrix4 modelMatrix;
	class Texture* texture;
	class Mesh* mesh;

public:
	Actor(const Actor&) = delete;
	Actor(Actor&&) = delete;
	Actor& operator=(const Actor&) = delete;
	Actor& operator=(Actor&&) = delete;



	Actor(Component* parent_);
	~Actor();
	bool OnCreate();
	void OnDestroy();
	void Update(const float deltaTime_);
	void Render() const;
	void ListComponents()const;

	template<typename ComponentTemplate, typename ... Args>
	void AddComponent(Args&& ... args_) {
		ComponentTemplate* comp = new ComponentTemplate(std::forward<Args>(args_)...);
		if (!dynamic_cast<Component*>(comp)) {
			///Trying to add a component that is not a base class of Component class
#ifdef _DEBUG
			std::cerr << "WARNING:Trying to add a component that is not a base class of Component class - ignored\n";
#endif
			delete comp;
			comp = nullptr;
			return;
		}
		if (GetComponent<ComponentTemplate>()) {
			///Trying to add a component type that is already added
#ifdef _DEBUG
			std::cerr << "WARNING:Trying to add a component type that is already added - ignored\n";
#endif
			delete comp;
			comp = nullptr;
			return;
		}
		components.push_back(comp);
		
	}

	template<typename ComponentTemplate>
	ComponentTemplate* GetComponent() {
		for (auto component : components) {
			if (dynamic_cast<ComponentTemplate*>(component)) {
				return dynamic_cast<ComponentTemplate*>(component);
			}
		}
		return nullptr;
	}

	template<typename ComponentTemplate>
	void RemoveComponent() {
		for (unsigned int i = 0; i < components.size(); i++) {
			if (dynamic_cast<ComponentTemplate*>(components[i])) {
				components[i]->OnDestroy();
				delete components[i];
				components[i] = nullptr;
				components.erase(components.begin() + i);
				break;
			}
		}
	}

	
	inline Matrix4 GetModelMatrix(){

		/*
		if(parent != nullptr){
			parent->Ge
		}
		*/
		return modelMatrix;
	}

	inline void SetModelMatrix(const Matrix4 &modelMatrix_){
		modelMatrix = modelMatrix_;
	}

	Texture* GetTexture(){return texture;}
	void SetTexture( Texture* texture_){texture = texture_;}

	Mesh* GetMesh(){return mesh;}
	void SetMesh( Mesh* mesh_){mesh = mesh_;}
	
};
