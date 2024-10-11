#include "camera.h"

Camera::Camera()
	: _position(0.f, 0.f, 0.f), _yaw(0.f), _pitch(0.f), _worldUp(0.f, 1.f, 0.f)
{
	
}

Camera::~Camera()
{

}

void Camera::update()
{
	if (_yaw >= 360)
	{
		_yaw = _yaw - 360;
	}
	else if (_yaw < 0)
	{
		_yaw = _yaw + 360;
	}

	vec3 front;
	front.x = cos(radians(_yaw)) * cos(glm::radians(_pitch));
	front.y = sin(radians(_pitch));
	front.z = sin(radians(_yaw)) * cos(radians(_pitch));
	_front	= normalize(front);

	_right	= normalize(cross(_front, _worldUp));
	_up		= normalize(cross(_right, _front));
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

void Camera::move(vec3 direction)
{
	_position += direction;
}

void Camera::rotate(float yaw, float pitch)
{
	_yaw += yaw;
	_pitch += pitch;
}

mat4 Camera::getViewMatrix()
{
	return lookAt(_position, _position + _front, _up);
}