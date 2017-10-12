#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
using namespace std;
using namespace glm;

Camera::Camera() {
	SetPerspective(1.0f, 1000.0f, 60.0f, 1.0f);
	// Inversa de la matriz modelo de la cámara
	_viewMatrix = inverse(_transform.GetModelMatrix());
}

mat4 Camera::GetViewProjection()
{
	return _prpjectionMatrix * _viewMatrix;
}

mat4 Camera::GetViewMatrix() 
{
	return mat4();
}

mat4 Camera::GetProjectionMatrix()
{
	return _prpjectionMatrix;
}

vec3 Camera::GetPosition()
{
	return _transform.GetPosition();
}

void Camera::SetPosition(float x, float y, float z)
{
	_transform.SetPosition(x, y, z);
	_viewMatrix = inverse(_transform.GetModelMatrix());
}

void Camera::SetRotation(float x, float y, float z) 
{
	_transform.SetRotation(x, y, z);
	_viewMatrix = inverse(_transform.GetModelMatrix());
}

void Camera::MoveForward(float delta, bool world) 
{
	_transform.MoveForward(delta, world);
	_viewMatrix = inverse(_transform.GetModelMatrix());
}

void Camera::MoveUp(float delta, bool world) 
{
	_transform.MoveUp(delta, world);
	_viewMatrix = inverse(_transform.GetModelMatrix());
}

void Camera::MoveRight(float delta, bool world) 
{
	_transform.MoveRight(delta, world);
	_viewMatrix = inverse(_transform.GetModelMatrix());
}

void Camera::Yaw(float degrees) 
{
	_transform.Rotate(0.0f,  degrees,0.0f,false);
	_viewMatrix = inverse(_transform.GetModelMatrix());
}

void Camera::Roll(float degrees)
{
	_transform.Rotate(0.0f, 0.0f, degrees, false);
	_viewMatrix = inverse(_transform.GetModelMatrix());
}

void Camera::Pitch(float degrees) 
{
		_transform.Rotate(degrees, 0.0f, 0.0f, false);
		_viewMatrix = inverse(_transform.GetModelMatrix());
}

void Camera::Rotate(float x, float y, float z, bool world) 
{
	_transform.Rotate(x, y, z, world);
	_viewMatrix = inverse(_transform.GetModelMatrix());
}

void Camera::SetPerspective(float nearPlane, float farPlane, float fieldOfView, float aspectRatio)
{
	_prpjectionMatrix = glm::perspective(glm::radians(fieldOfView), aspectRatio, nearPlane, farPlane);
}

void Camera::SetOrtographic(float size, float aspectRatio)
{
	float xSize = aspectRatio * size;
	_prpjectionMatrix = glm::ortho(-xSize, xSize, -size, size, -size, size);
}
