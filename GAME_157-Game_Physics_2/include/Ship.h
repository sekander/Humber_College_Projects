#ifndef SHIP_H
#define SHIP_H

#include "Physics.h"

class Ship : public Physics
{
    public:

        Ship(Vector2D position, Vector2D velocity, Vector2D acceleration, Vector2D force,
        long torque, long mass, double angle, double angularVelocity, double angularAcceleration, long rotational_inertia) :
        Physics(position, velocity, acceleration, force, torque, mass, angle, angularVelocity, angularAcceleration, rotational_inertia)
        {}

        ~Ship(){}

//    Ship(Vector2D position, Vector2D velocity, Vector2D acceleration, Vector2D force,
//    int mass, int torque, float angulaAcceleration):
//    position(position), velocity(velocity), acceleration(acceleration), force(force),
//    mass(mass), torque(torque), angularVelocity(angulaAcceleration){}
//    ~Ship();

    private:


};

#endif // SHIP_H
