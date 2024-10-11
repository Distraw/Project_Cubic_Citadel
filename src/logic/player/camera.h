#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
using namespace glm;

class Camera
{
private:
	vec3 _position;
	float _yaw;
	float _pitch;

	float _speed;
	float _sensitivity;
	float _fov;

	vec3 _front;
	vec3 _up;
	vec3 _right;
	vec3 _worldUp;
public:
	Camera();
	~Camera();
	
	void update();

	void setPosition(vec3 position);
	void setRotation(float yaw, float pitch);

	void move(vec3 direction);
	void rotate(float yaw, float pitch);

	mat4 getViewMatrix();
};