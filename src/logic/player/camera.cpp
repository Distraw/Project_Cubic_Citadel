#include "camera.h"

Camera::Camera()
	: _position(0, 0, 0), _rotation(0, 0)
{

}

void Camera::setPosition(vec3 position)
{
	_position = position;
}

void Camera::setRotation(vec3 rotation)
{
	_rotation = rotation;
}

void Camera::move(vec3 direction)
{
	_position += direction;
}

void Camera::rotate(vec3 turning)
{
	_rotation += turning;
}