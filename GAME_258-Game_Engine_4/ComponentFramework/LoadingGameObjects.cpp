#include "LoadingGameObjects.h"

#include "TransformComponent.h"
#include "MeshComponent.h"
#include "ShaderComponent.h"
#include "MaterialComponent.h"


LoadingGameObjects::LoadingGameObjects()
{}

LoadingGameObjects::~LoadingGameObjects()
{
	std::cout << "DELETING !!\n";
}

void LoadingGameObjects::ReadManifestScene0(const char* fileName)
{
	XMLDocument doc;
	doc.LoadFile(fileName);
	bool status = doc.Error();
	if (status) {
		std::cout << doc.ErrorIDToName(doc.ErrorID()) << std::endl;
		return;
	}


	XMLElement* rootData = doc.RootElement();
	XMLElement* sceneData = rootData->FirstChildElement("Scene0");


	XMLElement* cameraData = sceneData->FirstChildElement("Camera");
	XMLElement* cameraLocation = cameraData->FirstChildElement("Location");
	XMLElement* orientationData = cameraData->FirstChildElement("Orientation");


	std::cout << "File Loaded : " 
		<< "\n Camera Location X : " << cameraLocation->FloatAttribute("x")
		<< "\n Camera Location Y : " << cameraLocation->FloatAttribute("y")
		<< "\n Camera Location Z : " << cameraLocation->FloatAttribute("z")
		<< "\n" << orientationData->FloatAttribute("yaw")
		<< "\n" << orientationData->FloatAttribute("pitch")
		<< "\n" << orientationData->FloatAttribute("roll")
	<< std::endl;

	XMLElement* lightData = sceneData->FirstChildElement("Light");
	XMLElement* lightLocation = lightData->FirstChildElement("Location");
	XMLElement* lightColour = lightData->FirstChildElement("Colour");

	std::cout << "File Loaded : "
		<< "\n Light Location X : " << lightLocation->FloatAttribute("x")
		<< "\n Light Location Y : " << lightLocation->FloatAttribute("y")
		<< "\n Light Location Z : " << lightLocation->FloatAttribute("z")
		<< "\n Light Color R :" << lightColour->FloatAttribute("red")
		<< "\n Light Color G :" << lightColour->FloatAttribute("green")
		<< "\n Light Color B :" << lightColour->FloatAttribute("blue")
	<< std::endl;

	set_vec4(Vec4(lightColour->FloatAttribute("red"), 
				  lightColour->FloatAttribute("green"), 
				  lightColour->FloatAttribute("blue"), 0.0));



	XMLElement* entityData = sceneData->FirstChildElement("Entity");
	while (entityData)
	{
		XMLElement* meshData = entityData->FirstChildElement("Mesh");
		XMLElement* textureData = entityData->FirstChildElement("Texture");
		XMLElement* locationData = entityData->FirstChildElement("Location");



		std::cout << "File Loaded : "
			<< "\n Mesh Name : " << meshData->Attribute("meshname")
			<< "\n Mesh FileName : " << meshData->Attribute("filename")
			<< "\n Texture Name  : " << textureData->Attribute("textureName")
			<< "\n Texture FileName  : " << textureData->Attribute("filename")
			<< "\n Location X :" << locationData->FloatAttribute("x")
			<< "\n Location Y :" << locationData->FloatAttribute("y")
			<< "\n Location Z :" << locationData->FloatAttribute("z")
		<< std::endl;

		
		actor = std::make_shared<Actor>(nullptr);
		actor->AddComponent<TransformComponent>(nullptr, Vec3(locationData->FloatAttribute("x"), 
															  locationData->FloatAttribute("y"),
															  locationData->FloatAttribute("z")), Quaternion());
		actor->AddComponent<MeshComponent>(nullptr, meshData->Attribute("filename"));
		actor->AddComponent<MaterialComponent>(nullptr, textureData->Attribute("filename"));
		actor->AddComponent<ShaderComponent>(nullptr, "shaders/textureVert.glsl", "shaders/textureFrag.glsl");
		actor->OnCreate();



		actors_map.insert(std::make_pair(meshData->Attribute("meshname"), actor));

		


		entityData = entityData->NextSiblingElement("Entity");
	}



}

void LoadingGameObjects::ReadManifestScene1(const char* fileName)
{
	XMLDocument doc;
	doc.LoadFile(fileName);
	bool status = doc.Error();
	if (status) {
		std::cout << doc.ErrorIDToName(doc.ErrorID()) << std::endl;
		return;
	}
	std::cout << "File Loaded : " << fileName << std::endl;

	
	XMLElement* rootData = doc.RootElement();
	XMLElement* sceneData = rootData->FirstChildElement("Scene1");


	XMLElement* cameraData = sceneData->FirstChildElement("Camera");
	XMLElement* cameraLocation = cameraData->FirstChildElement("Location");
	XMLElement* orientationData = cameraData->FirstChildElement("Orientation");

	
	std::cout << "File Loaded : " << "\n Camera Location X : " << cameraLocation->FloatAttribute("x")
								  << "\n Camera Location Y : " << cameraLocation->FloatAttribute("y")
								  << "\n Camera Location Z : " << cameraLocation->FloatAttribute("z")
								  << "\n" << orientationData->FloatAttribute("yaw")
								  << "\n" << orientationData->FloatAttribute("pitch")
								  << "\n" << orientationData->FloatAttribute("roll")

	<<	std::endl;

	
	/*
	Vec3 location;
	location.x = cameraLocation->FloatAttribute("x");
	location.y = cameraLocation->FloatAttribute("y");
	location.z = cameraLocation->FloatAttribute("z");
	location.print();

c	Vec3 orientation;
	orientation.x = orientationData->FloatAttribute("yaw");
	orientation.y = orientationData->FloatAttribute("pitch");
	orientation.z = orientationData->FloatAttribute("roll");
	orientation.print();
	*/
}

