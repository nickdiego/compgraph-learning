// Transform.cpp: implementation of the Transform class.


#include "Transform.h"
#include <iostream>

using namespace std;

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  float angle = degrees * M_PI / 180.0f;
  mat3 r1(cos(angle));
  mat3 r2(0, -axis.z, axis.y, axis.z, 0, -axis.x, -axis.y, axis.x, 0);
  mat3 r3(axis.x*axis.x, axis.x*axis.y, axis.x*axis.z,
          axis.x*axis.y, axis.y*axis.y, axis.y*axis.z,
          axis.x*axis.z, axis.z*axis.y, axis.z*axis.z);
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
        r2[i][j] = r2[i][j]*sin(angle);
        r3[i][j] = r3[i][j]*(1-cos(angle));
    }
  }
  return r1 + r2 + r3;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  eye = eye * rotate(degrees, up);
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {

  vec3 axis = glm::normalize(glm::cross(eye, up));
  eye = eye * rotate(degrees, axis);
  up = up * rotate(degrees, axis);
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  vec3 center(0.0, 0.0, 0.0);
  return glm::lookAt(eye, center, up);
}

Transform::Transform()
{
}

Transform::~Transform()
{
}
