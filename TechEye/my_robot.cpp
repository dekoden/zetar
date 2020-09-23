#include "my_robot.h"

MyRobot::MyRobot()
{

}

MyRobot::MyRobot(float width, float height,
				 float wheelWidth, float wheelDiameter,
				 float speed = 0, float angularSpeed = 0)
{
	m_width = width;
	m_height = height;
	m_wheelWidth = wheelWidth;
	m_wheelDiameter = wheelDiameter;
}

//Setters
void MyRobot::setSpeed(float speed)
{
	m_speed = speed;
}
void MyRobot::setAngularSpeed(float angularSpeed)
{
	m_angularSpeed = angularSpeed;
}
void MyRobot::setArea(const Size2i area)
{
	m_area = area;
}
int MyRobot::setArea(Mat image)
{
	if (image.empty())
	{
		return -1;
	}
	m_area.width = image.cols;
	m_area.height = image.rows;
	return 0;
}
int MyRobot::setCenter(Mat image)
{
	if (image.empty())
	{
		return -1;
	}
	if ((image.cols / 2 > m_area.width) ||
		(image.rows / 2 > m_area.height))
	{
		return -2;
	}
	m_center.x = image.cols / 2;
	m_center.y = image.rows / 2;

	return 0;
}
int MyRobot::setCenter(float x, float y)
{
	if ((x > m_area.width) ||
		(y > m_area.height))
	{
		return -1;
	}
	m_center.x = x;
	m_center.y = y;

	return 0;
}

//Getters
float MyRobot::getSpeed()
{
	return m_speed;
}
float MyRobot::getAngularSpeed()
{
	return m_angularSpeed;
}


int MyRobot::draw(Mat& ioImage)
{
	if (ioImage.empty())
	{
		return -1;
	}

	if ((ioImage.cols != m_area.width) ||
		(ioImage.rows != m_area.height))
	{
		return -2;
	}
}


bool MyRobot::rotate()
{

}

bool MyRobot::move()
{

}