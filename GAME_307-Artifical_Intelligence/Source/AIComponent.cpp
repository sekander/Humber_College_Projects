#include "../../include/Components/AIComponent.h"
#include <box2d/b2_math.h>
#include <iostream>

AIComponent::AIComponent(Component* parent_  ) : Component(parent_)
{
	std::cout << "AI Component Attached" << std::endl;

}

AIComponent::~AIComponent()
{
	std::cout << "AI Component Removed\n";

	for(auto &pos : aiPositions)
	{
		delete pos;
	}

	aiPositions.clear();
}

void AIComponent::update(const float delta)
{

}

//Seek algorithm impleentation
//otherBody : seeking b2Body
//y : added gravity vector
b2Vec2 AIComponent::seek(b2Body *otherBody, float maxSpeed, float gravity)
{
	//Find the vector between AI and otherbody
	auto result = otherBody->GetPosition() - m_body->GetPosition();
	//Calculate the direction of given vector
	result.Normalize();

	//Tranform unit vector to add velocity 
	//Max Speed
	result *= maxSpeed;

	//AI jump velocity
	//Copy otherbody velocity
	auto ai_jump = otherBody->GetLinearVelocity().y * 0.80;

	//Set the new vector to AI body physic 	
	return b2Vec2(result.x, ai_jump + gravity);
//	m_body->SetLinearVelocity(b2Vec2(result.x,  ai_jump + y));
}

//Flee algorithm impleentation
//otherBody : seeking b2Body
//y : added gravity vector
b2Vec2 AIComponent::flee(b2Body *otherBody, float maxSpeed, float gravity)
{
	//Find the vector between AI and otherbody
	auto result = m_body->GetPosition() - otherBody->GetPosition()  ;
	//Calculate the direction of given vector
	result.Normalize();
	//Tranform unit vector to add velocity 
	result *= maxSpeed;

	//AI jump velocity
	//Copy otherbody velocity
	auto ai_jump = otherBody->GetLinearVelocity().y * 0.80;

	//Set the new vector to AI body physic 	
	return b2Vec2(result.x, ai_jump + gravity);
}

//Basic wander algorithm
//
//Future Implementation
//Add Randomness to the distance
b2Vec2 AIComponent::wander( float minDistance, float maxSpeed, float maxDistance)
{
	m_position = m_body->GetPosition();

//	std::cout << "Pos x : " << m_position.x << std::endl; 
//	std::cout << "Pos y : " << m_position.y << std::endl; 


	//Change position once AI reached minDistance
	if(m_position.x < beginningPosition - minDistance )
		m_body->SetLinearVelocity(b2Vec2(maxSpeed,0.0f));	
	//Change position once AI reached minDistance
	else if(m_position.x > beginningPosition + maxDistance)
		m_body->SetLinearVelocity(b2Vec2(-maxSpeed, 0.0f));	
	//Update AI position
	return b2Vec2(m_position);
}

