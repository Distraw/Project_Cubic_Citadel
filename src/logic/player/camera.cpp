#include "camera.h"

Camera::Camera()
	: _position(64.f, 12.f, 64.f), _yaw(90.f), _pitch(0.f), _worldUp(0.f, 1.f, 0.f),
	_fov(90.f), _speed(7.f)
{
	
}

Camera::~Camera()
{

}

void Camera::update()
{
	if (_yaw >= 360)	_yaw = _yaw - 360;
	else if (_yaw < 0)	_yaw = _yaw + 360;

	if (_pitch >= 89)		_pitch = 89;
	else if (_pitch <= -89)	_pitch = -89;
		

	vec3 front;
	front.x = cos(radians(_yaw)) * cos(glm::radians(_pitch));
	front.y = sin(radians(_pitch));
	front.z = sin(radians(_yaw)) * cos(radians(_pitch));

	_front	= normalize(front);

	_right	= normalize(cross(_front, _worldUp));
	_up		= normalize(cross(_right, _front));
}

void Camera::setPosition(float x, float y, float z)
{
	_position = vec3(x, y, z);
}

void Camera::setPosition(vec3 position)
{
	_position = position;
}

void Camera::setRotation(float yaw, float pitch)
{
	_yaw = yaw;
	_pitch = pitch;
}

void Camera::setDeltaTimePtr(const double* delta_time)
{
	_delta_time = delta_time;
}

vec3 Camera::getFrontVector()
{
	return _front;
}

vec3 Camera::getPosition()
{
	return _position;
}

mat4 Camera::getViewMatrix()
{
	return lookAt(_position, _position + _front, _up);
}

mat4 Camera::getProjectionMatrix()
{
	return perspective(radians(90.f), 1.f, 0.1f, 1000.f);
}

void Camera::move(float x, float y, float z)
{
	_position += vec3(x, y, z);
}

void Camera::move(vec3 direction)
{
	_position += direction;
}

void Camera::definedMove(int x, int y, int z)
{
	double delta_speed = (*_delta_time) * _speed;
	vec3 dir = vec3(0, 0, 0);
	if (z == 1)
	{
		dir.z = sin(radians(_yaw)) * delta_speed;
		dir.x = cos(radians(_yaw)) * delta_speed;
	}
	else if (z == -1)
	{
		dir.z = -sin(radians(_yaw)) * delta_speed;
		dir.x = -cos(radians(_yaw)) * delta_speed;
	}

	if (x == 1)
	{
		dir.z = cos(radians(_yaw)) * delta_speed;
		dir.x = -sin(radians(_yaw)) * delta_speed;
	}
	else if (x == -1)
	{
		dir.z = -cos(radians(_yaw)) * delta_speed;
		dir.x = sin(radians(_yaw)) * delta_speed;
	}

	if (y == 1)
	{
		dir.y = delta_speed;
	}
	else if (y == -1)
	{
		dir.y = -delta_speed;
	}

	

	this->move(dir);
}

void Camera::rotate(float yaw, float pitch)
{
	_yaw += yaw;
	_pitch += pitch;
}