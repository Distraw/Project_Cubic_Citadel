#pragma once
#include "glm/glm.hpp"
using namespace glm;

class Camera
{
private:
	vec3 _position;
	vec2 _rotation;
public:
	Camera();
	~Camera();

	void setPosition(vec3 position);
	void setRotation(vec3 rotation);

	void move(vec3 direction);
	void rotate(vec3 turning);
};