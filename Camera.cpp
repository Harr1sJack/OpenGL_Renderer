#include "Camera.h"

Camera::Camera(int _width, int _height, glm::vec3 _position)
{
	Camera::width = _width;
	Camera::height = _height;
	Camera::position = _position;
}

void Camera::UpdateMatrix(float FOV_deg, float nearPlane, float farPlane)
{
	view = glm::lookAt(position, position + orientation, up);
	proj = glm::perspective(glm::radians(FOV_deg), (float)width / height, nearPlane, farPlane);

}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(proj * view));
}

void Camera::Inputs(GLFWwindow* window)
{
	//WASD movements
	if (glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS) 
	{
		position += speed * orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position += speed * -glm::normalize(glm::cross(orientation, up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position += speed * -orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position += speed * glm::normalize(glm::cross(orientation, up));
	}
	
	//up and down movements
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		position += speed * up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		position += speed * -up;
	}

	//speed of camera
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.08f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 0.03f;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) 
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		if (firstClick) 
		{
			glfwSetCursorPos(window, (double)(width / 2), (double)(height / 2));
			firstClick = false;
		}

		double mouseX;
		double mouseY;

		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = sensitivity * (float)(mouseX - height / 2) / height;
		float rotY = sensitivity * (float)(mouseY - height / 2) / height;

		glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotY), glm::normalize(glm::cross(orientation, up)));
		if (!((glm::angle(newOrientation,up)<=glm::radians(5.0f)) or(glm::angle(newOrientation,-up)<=glm::radians(5.0f))))
		{
			orientation = newOrientation;
		}
		orientation = glm::rotate(orientation, glm::radians(-rotX), up);
		glfwSetCursorPos(window, (double)(width / 2), (double)(height / 2));

	}
	else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		firstClick = true;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}
