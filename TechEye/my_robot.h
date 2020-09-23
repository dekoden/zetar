#pragma once
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

class MyRobot
{
	MyRobot();
	MyRobot(float width, float height,
			float wheelWidth, float wheelDiameter,
			float speed = 0, float angularSpeed = 0);
	~MyRobot();

	//Setters
	void setSpeed(float speed);
	void setAngularSpeed(float angularSpeed);
	void setArea(const Size2i area);
	int setArea(Mat image);
	int setCenter(Mat image);
	int setCenter(float x, float y);

	float getSpeed();
	float getAngularSpeed();

	bool rotate();
	bool move();

	int draw(Mat& ioImage);


private:
	Point2f m_center;
	float m_angle;
	float m_width;
	float m_height;
	float m_wheelWidth;
	float m_wheelDiameter;
	float m_speed;
	float m_angularSpeed;
	Size2i m_area;
};
