
#include <SFML/Graphics.hpp>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Glsl.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <iostream>


#include "Physics.h"

/*
bool circle_ray_detection(ray& r, sf::CircleShape c)
{
	  auto a = dot(r.dir, r.dir);
          auto b = 2 * (dot(r.start, r.dir));
          auto e = (dot(r.start, r.start) - (c.getRadius() * c.getRadius()));
  
          auto d = b*b - 4 * (a*e);
  
          if(d < 0)
                  return false;
          if(d > 0)
                  return true;
//	return false;
}
*/



int circle_detection(sf::CircleShape c1, sf::CircleShape c2)
{
	int distSq = ((c1.getPosition().x - c2.getPosition().x) * 
		     (c1.getPosition().x - c2.getPosition().x)) +
		     ((c1.getPosition().y - c2.getPosition().y) * 
		     (c1.getPosition().y - c2.getPosition().y)); 
	
	int radSumSq = (c1.getRadius() + c2.getRadius()) *
		       (c1.getRadius() + c2.getRadius());

	if(distSq == radSumSq)
		return 1;
	else if (distSq > radSumSq)
		return -1;
	else
		return 0;
}


int main()
{
	//sf::RenderWindow window = sf::RenderWindow{ { 800, 800 }, "The Book of Shaders" };
	sf::RenderWindow window;   
	window.create(sf::VideoMode(800, 600), "Nahid Window", sf::Style::Close);
    window.setFramerateLimit(144);

    auto clock = sf::Clock{};


    ray floor(vec_3(50.0f, 550.0f), vec_3(750.0f, 550.0f));
    ray left_side(vec_3(50.0f, 50.0f), vec_3(50.0f, 550.0f));
    ray right_side(vec_3(750.0f, 50.0f), vec_3(750.0f, 550.0f));


    ray water_left_side(vec_3(50.0f, 550.0f), vec_3(50.0f, 325.0f));
    ray water_roof(vec_3(50.0f, 325.0f),vec_3(325.0f, 325.0f)); 
    ray water_right_side(vec_3(325.0f, 325.0f), vec_3(325.0f, 550.0f));
    ray water_bottom(vec_3(325.0f, 550.0f), vec_3(50.0f, 550.0f));

    //275 * 275

    sf::Vertex line[] = {
   	sf::Vertex(sf::Vector2f(floor.start.x, floor.start.y), sf::Color(0.0f, 255.0f, 0.0f)), 
   	sf::Vertex(sf::Vector2f(floor.dir.x, floor.dir.y), sf::Color(0.0f, 255.0f, 0.0f)), 
   	sf::Vertex(sf::Vector2f(left_side.start.x, left_side.start.y), sf::Color(255.0f, 0.0f, 0.0f)), 
   	sf::Vertex(sf::Vector2f(left_side.dir.x, left_side.dir.y), sf::Color(255.0f, 0.0f, 0.0f)), 
   	sf::Vertex(sf::Vector2f(right_side.start.x, right_side.start.y), sf::Color(255.0f, 0.0f, 0.0f)), 
   	sf::Vertex(sf::Vector2f(right_side.dir.x, right_side.dir.y), sf::Color(255.0f, 0.0f, 0.0f)), 

	sf::Vertex(sf::Vector2f(water_left_side.start.x, water_left_side.start.y), sf::Color(0.0f, 0.0f, 255.0f)),
	sf::Vertex(sf::Vector2f(water_left_side.dir.x, water_left_side.dir.y), sf::Color(0.0f, 0.0f, 255.0f)),
	sf::Vertex(sf::Vector2f(water_roof.start.x, water_roof.start.y), sf::Color(0.0f, 0.0f, 255.0f)),
	sf::Vertex(sf::Vector2f(water_roof.dir.x, water_roof.dir.y), sf::Color(0.0f, 0.0f, 255.0f)),
	sf::Vertex(sf::Vector2f(water_right_side.start.x, water_right_side.start.y), sf::Color(0.0f, 0.0f, 255.0f)),
	sf::Vertex(sf::Vector2f(water_right_side.dir.x, water_right_side.dir.y), sf::Color(0.0f, 0.0f, 255.0f)),
	sf::Vertex(sf::Vector2f(water_bottom.start.x, water_bottom.start.y), sf::Color(0.0f, 0.0f, 255.0f)),
	sf::Vertex(sf::Vector2f(water_bottom.dir.x, water_bottom.dir.y), sf::Color(0.0f, 0.0f, 255.0f)),
	
    };


    plane p_axis(vec_3(400.0f, 300.0f), 0.0f);


    Sphere circle_1;
    circle_1.position.x = 250.0f;
    circle_1.position.y = 150.0f;
    circle_1.radius = 25.0f;

    sf::CircleShape circle(circle_1.radius);
    circle.setPosition(circle_1.position.x, circle_1.position.y);
    circle.setFillColor(sf::Color(100, 250, 50));


    Sphere circle_2;
    circle_2.position.x = 400.0f;
    circle_2.position.y = 200.0f;
    circle_2.radius = 25.0f;

    sf::CircleShape circle2(circle_2.radius);
    circle2.setPosition(circle_2.position.x, circle_2.position.y);
    circle2.setFillColor(sf::Color(200, 110, 50));

    Sphere circle_3;
    circle_3.position.x = 333.0f;
    circle_3.position.y = 250.0f;
    circle_3.radius = 25.0f;

    sf::CircleShape circle3(circle_3.radius);
    circle3.setPosition(circle_3.position.x, circle_3.position.y);
    circle3.setFillColor(sf::Color(100, 210, 150));
    

   vec_3 position; 
   vec_3 velocity; 
   vec_3 force; 
   vec_3 acceleration; 


   vec_3 gravity;

   //Buyancy Test
   //volume for sumere object
   auto bouyancy = 1000  * -9.8 *  0.0025; 

   int mass;
   int torque;
   float angle;
   float angularAcceleration;
   long rotational_inertia;
   float angularVelocity;

   Physics *p_body_1, *p_body_2, *p_body_3; 
   Physics *water_body;
   p_body_1 = new Physics(position, velocity, acceleration, force, torque, mass, angle, 
		   angularVelocity, angularAcceleration, rotational_inertia);

    p_body_1->position.x = 200.0f;
    p_body_1->position.y = 220.0f;
    p_body_1->velocity.x = 0.0f;
    p_body_1->velocity.y = 0.0f;
    p_body_1->acceleration.x = 0.0f;
    p_body_1->acceleration.y =0.0f;
    p_body_1->force.x = 0;
    p_body_1->force.y = 0.0f;
    p_body_1->torque = 10;
    p_body_1->torque = 0;
    p_body_1->mass = 1000;
    p_body_1->angle = 0.0f;
    p_body_1->angularAcceleration = 0.0f;
    p_body_1->angularVelocity = 0.0f;
    p_body_1->rotational_inertia = 50.0f;
    p_body_1->radius = circle.getRadius();


   p_body_2 = new Physics(position, velocity, acceleration, force, torque, mass, angle, 
		   angularVelocity, angularAcceleration, rotational_inertia);

    p_body_2->position.x = 500.0f;
    p_body_2->position.y = 200.0f;
    p_body_2->velocity.x = 0.0f;
    p_body_2->velocity.y = 0.0f;
    p_body_2->acceleration.x = 0.0f;
    p_body_2->acceleration.y =0.0f;
    p_body_2->force.x = 0;
    p_body_2->force.y = 0.0f;
    p_body_2->torque = 10;
    p_body_2->torque = 0;
    p_body_2->mass = 1000000;
    p_body_2->angle = 0.0f;
    p_body_2->angularAcceleration = 0.0f;
    p_body_2->angularVelocity = 0.0f;
    p_body_2->rotational_inertia = 50.0f;
    p_body_2->radius = circle2.getRadius();

    p_body_3 = new Physics(position, velocity, acceleration, force, torque, mass, angle, 
		   angularVelocity, angularAcceleration, rotational_inertia);

    p_body_3->position.x = 400.0f;
    p_body_3->position.y = 450.0f;
    p_body_3->velocity.x = 0.0f;
    p_body_3->velocity.y = 0.0f;
    p_body_3->acceleration.x = 0.0f;
    p_body_3->acceleration.y =0.0f;
    p_body_3->force.x = 0;
    p_body_3->force.y = 0.0f;
    p_body_3->torque = 10;
    p_body_3->torque = 0;
    p_body_3->mass = 10000;
    p_body_3->angle = 0.0f;
    p_body_3->angularAcceleration = 0.0f;
    p_body_3->angularVelocity = 0.0f;
    p_body_3->rotational_inertia = 50.0f;
    p_body_3->radius = circle2.getRadius();

    auto mouse_position = sf::Vector2f{};
    sf::Vector2f pos = sf::Vector2f(10.0f, 10.0f);	

    while (window.isOpen())
    {

	p_body_1->calculateAngularAcceleration();
	p_body_1->calculateAngularVelocity(p_body_1->angularAcceleration, 1 );
	p_body_1->calculateAngle(p_body_1->angularVelocity, p_body_1->angularAcceleration, 1 );
	p_body_1->calculateForce(p_body_1->force, p_body_1->angle);
	p_body_1->calculatePosition(p_body_1->position, p_body_1->velocity, p_body_1->acceleration, 1);
        p_body_1->calculateVelocity(p_body_1->velocity, p_body_1->acceleration, 1);
        p_body_1->calculateAcceleration(p_body_1->force, p_body_1->mass);

	p_body_2->calculateAngularAcceleration();
	p_body_2->calculateAngularVelocity(p_body_2->angularAcceleration, 1 );
	p_body_2->calculateAngle(p_body_2->angularVelocity, p_body_2->angularAcceleration, 1 );
	p_body_2->calculateForce(p_body_2->force, p_body_2->angle);
	p_body_2->calculatePosition(p_body_2->position, p_body_2->velocity, p_body_2->acceleration, 1);
        p_body_2->calculateVelocity(p_body_2->velocity, p_body_2->acceleration, 1);
        p_body_2->calculateAcceleration(p_body_2->force, p_body_2->mass);

	p_body_3->calculateAngularAcceleration();
	p_body_3->calculateAngularVelocity(p_body_3->angularAcceleration, 1 );
	p_body_3->calculateAngle(p_body_3->angularVelocity, p_body_3->angularAcceleration, 1 );
	p_body_3->calculateForce(p_body_3->force, p_body_3->angle);
	p_body_3->calculatePosition(p_body_3->position, p_body_3->velocity, p_body_3->acceleration, 1);
        p_body_3->calculateVelocity(p_body_3->velocity, p_body_3->acceleration, 1);
        p_body_3->calculateAcceleration(p_body_3->force, p_body_3->mass);

	circle.setPosition(p_body_1->position.x, p_body_1->position.y);
	circle_1.position = p_body_1->position;
	circle_1.radius = p_body_1->radius;

	circle2.setPosition(p_body_2->position.x, p_body_2->position.y);
	circle3.setPosition(p_body_3->position.x, p_body_3->position.y);


	gravity.x = 0.0f;
	gravity.y = 9.8f;

	p_body_1->force.y = gravity.y;
	p_body_2->force.y = gravity.y;
	p_body_3->force.y = gravity.y;

	std::cout << bouyancy << std::endl;
	p_body_1->position.print_vec();

	if(p_body_1->position.y > 300 && 
	   p_body_1->position.x < 300)
		p_body_1->force.y =  bouyancy  ;

        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed || 
	 	event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }

	    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
	    {
		    p_body_1->force.x += 0.001f;
	    }
	    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
	    {
		    p_body_1->force.x -= 0.001f;
	    }
	    else{
	    	//p_body_1->force.x = 0.0f;
	    }

	    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W)
	    {
		    p_body_1->force.y += 0.001f;
	    }
	    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
	    {
		    p_body_1->force.y -= 0.001f;
	    }
	    
	    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
	    {
	    	p_body_1->velocity.x = 0.0f;
	    	p_body_1->velocity.y = 0.0f;
		p_body_1->angularVelocity = 0.0f;
		p_body_1->force.x = 0.0f;
		p_body_1->force.y = 0.0f;
	    }
	    
	    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
	    {
		    p_body_3->force.x += 0.01f;
	    }
	    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
	    {
		    p_body_3->force.x -= 0.01f;
	    }
	    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
	    {
		    p_body_3->force.y += 0.01f;
	    }
	    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
	    {
		    p_body_3->force.y -= 0.01f;
	    }
	    
	    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
	    {
	    	p_body_2->velocity.x = 0.0f;
	    	p_body_2->velocity.y = 0.0f;
		p_body_2->angularVelocity = 0.0f;
		p_body_2->force.x = 0.0f;
		p_body_2->force.y = 0.0f;
	    }
        }
	
	/*
	std::cout << "Circle 1 POS: " << p_body_1->position.x << " , " << p_body_1->position.y 
		  << "\nRadius: " << p_body_1->radius 
		<< std::endl;
	std::cout << "Circle 2 POS: " << p_body_2->position.x << " , " << p_body_2->position.y 
		  << "\nRadius: " << p_body_2->radius 
		<< std::endl;
	*/
	checkFloorCollision(*p_body_1, floor);	
	checkFloorCollision(*p_body_2, floor);	
	checkFloorCollision(*p_body_3, floor);	
	checkLeftWallCollision(*p_body_1, left_side);	
	//checkLeftWallCollision(*p_body_1, right_side);	
	//checkRightWallCollision(*p_body_3, y_axis);	
	//checkRoofCollision(*p_body_2, x_axis);



	//checkFloorCollision(*p_body_2, x_axis);
	//checkRightWallCollision(*p_body_2, y_axis);

	int c = circle_detection(circle, circle3);

	if(c == 1){
		std::cout << "Circle touch each other\n";
		//SphereStaticSphereCollisionResponse(*p_body_1, *p_body_3);
		SphereSphereCollisionResponse(*p_body_1, *p_body_3, 1.0f);
	}
	else if(c < 0)
		std::cout << "Circle do not touch\n";
	else
	{
		std::cout << "Circles are intersecting\n";
		//SphereStaticSphereCollisionResponse(*p_body_1, *p_body_3);
		SphereSphereCollisionResponse(*p_body_1, *p_body_3, 1.0f);
	}

	int t = circle_detection(circle, circle2);

	if(t == 1){
		std::cout << "Circle touch each other\n";
		SphereStaticSphereCollisionResponse(*p_body_1, *p_body_2);
		//SphereSphereCollisionResponse(*p_body_1, *p_body_2, 1.0f);
	}
	else if(t < 0)
		std::cout << "Circle do not touch\n";
	else
	{
		std::cout << "Circles are intersecting\n";
		SphereStaticSphereCollisionResponse(*p_body_1, *p_body_2);
		//SphereSphereCollisionResponse(*p_body_1, *p_body_2, 1.0f);
	}
        window.clear();
        window.draw(circle);
        window.draw(circle2);
        window.draw(circle3);
	window.draw(line, 14, sf::Lines);
        window.display();
    }
}


