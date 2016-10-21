#ifndef CAMERA_H
#define CAMERA_H
#include "WindowClass.h"

class Camera
{
public:
	Camera(float sensibility,float speed,glm::vec3 vertical,float FOV,float ratio,float near,float far);
	Camera(Uint16 left, Uint16 right, Uint16 bottom, Uint16 top);
	~Camera();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

	void Move(SDL_Event &event);

	void orienter(int xRel, int yRel);
	void invert_pitch();
	void move(const glm::vec3 &position);
	glm::vec3 getPosition() { return m_position; }

private:
	float sensibility;
	float speed;
	float m_phi;
	float m_theta;
	glm::vec3 m_orientation;
	glm::vec3 m_vertical;
	glm::vec3 m_lateral;
	glm::vec3 m_position;
	glm::vec3 m_aim;
	glm::mat4 m_projection;
	
	int x, y, x2, y2;
	int *x1;
	int *y1;

	
	

};

#endif
