#pragma once

#include <iostream>
#include <unordered_map>

#include "Actor.h"
#include "tinyxml2.h"


using namespace tinyxml2;
class LoadingGameObjects
{
public:
	LoadingGameObjects();
	~LoadingGameObjects();

	void ReadManifestScene0(const char* fileName);
	void ReadManifestScene1(const char* fileName);
	
	Vec4 return_light_color() { return temp; }
	void set_vec4(Vec4 input) { temp = input; }

	std::unordered_map<std::string, Ref<Actor>> ReturnMap() {
		return actors_map;
	}

private:
	std::unordered_map<std::string, Ref<Actor>> actors_map;



	Vec4 temp;
	Ref<Actor> actor;


};

