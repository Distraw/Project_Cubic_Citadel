#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
using namespace glm;

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Camera
{
private:
	vec3 _position;
	float _yaw;
	float _pitch;
	float _fov;

	float _speed;
	float _sensitivity;

	vec3 _front;
	vec3 _up;
	vec3 _right;
	vec3 _worldUp;

	const double* _delta_time;
public:
	Camera();
	~Camera();

	void update();

	void setPosition(float x, float y, float z);
	void setPosition(vec3 position);
	void setRotation(float yaw, float pitch);
	void setDeltaTimePtr(const double* delta_time);

	mat4 getViewMatrix();
	mat4 getProjectionMatrix();

	void move(float x, float y, float z);
	void move(vec3 direction);
	void definedMove(int x, int y, int z);
	void definedMove(vec3 direction);
	void rotate(float yaw, float pitch);
};