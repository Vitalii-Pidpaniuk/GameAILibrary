#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <cstdlib>

struct Vector {
    float x = 0;
    float y = 0;

    Vector operator+(const Vector& other) const {
        return { x + other.x, y + other.y };
    }

    Vector operator-(const Vector& other) const {
        return { x - other.x, y - other.y };
    }

    Vector operator*(float scalar) const {
        return { x * scalar, y * scalar };
    }

    float length() const {
        return std::sqrt(x * x + y * y);
    }

    void normalize() {
        float len = length();
        if (len > 0) {
            x /= len;
            y /= len;
        }
    }
};

struct SteeringOutput {
    Vector linear;
    float angular = 0;
};

struct Kinematic {
    Vector position;
    float orientation = 0;
    Vector velocity;
    float rotation = 0;

    void update(const SteeringOutput& steering, float time) {
        position = position + velocity * time;
        orientation += rotation * time;

        velocity = velocity + steering.linear * time;
        rotation += steering.angular * time;
    }
};

float newOrientation(float current, const Vector& velocity) {
    if (velocity.length() > 0) {
        return std::atan2(-velocity.x, velocity.y);
    }
    return current;
}

class KinematicSeek {
public:
    Kinematic* character;
    Kinematic* target;
    float maxSpeed;

    SteeringOutput getSteering() {
        SteeringOutput result;
        result.linear = target->position - character->position;
        result.linear.normalize();
        result.linear = result.linear * maxSpeed;
        character->orientation = newOrientation(character->orientation, result.linear);
        result.angular = 0;
        return result;
    }
};

class KinematicAvoid {
public:
    Kinematic* character;
    Kinematic* obstacle;
    float avoidDistance;
    float maxSpeed;

    SteeringOutput getSteering() {
        SteeringOutput result;
        Vector toObstacle = obstacle->position - character->position;
        if (toObstacle.length() < avoidDistance) {
            result.linear = character->position - obstacle->position;
            result.linear.normalize();
            result.linear = result.linear * maxSpeed;
        }
        else {
            result.linear = { 0, 0 };
        }
        result.angular = 0;
        return result;
    }
};
