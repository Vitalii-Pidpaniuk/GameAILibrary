#include <iostream>
#include <vector>
#include <queue>
#include <memory>
#include <unordered_map>
#include <cmath>
#include <algorithm>
using namespace std;

class CharacterMovement {
public:
    struct Vector2 {
        float x, y;

        Vector2 operator+(const Vector2& other) const {
            return { x + other.x, y + other.y };
        }

        Vector2 operator-(const Vector2& other) const {
            return { x - other.x, y - other.y };
        }

        Vector2 operator*(float scalar) const {
            return { x * scalar, y * scalar };
        }

        float magnitude() const {
            return std::sqrt(x * x + y * y);
        }

        Vector2 normalize() const {
            float mag = magnitude();
            return { x / mag, y / mag };
        }
    };

    CharacterMovement(Vector2 position, float speed) : position(position), speed(speed) {}

    void moveTo(Vector2 target) {
        Vector2 direction = (target - position).normalize();
        position = position + direction * speed;
        std::cout << "Character moved to position: (" << position.x << ", " << position.y << ")" << std::endl;
    }

    void avoidObstacle(Vector2 obstacle, float avoidRadius) {
        Vector2 toObstacle = position - obstacle;
        if (toObstacle.magnitude() < avoidRadius) {
            Vector2 avoidDirection = toObstacle.normalize();
            position = position + avoidDirection * speed;
            std::cout << "Avoided obstacle, new position: (" << position.x << ", " << position.y << ")" << std::endl;
        }
    }

    Vector2 getPosition() const {
        return position;
    }

private:
    Vector2 position;
    float speed;
};