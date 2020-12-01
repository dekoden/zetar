#include "pch.h"
#include <opencv2/opencv.hpp>
#include "main.h"
#include <fstream>

cv::Mat frame;
int numOfCalibFrames = 10;
bool isCalibFrame = false;
int i = 0;
int CHECKERBOARD[2]{ 6,9 };
std::vector<cv::Point3f> objp;
std::vector<std::vector<cv::Point3f> > objpoints;
std::vector<std::vector<cv::Point2f> > imgpoints;
cv::Mat cameraMatrix, distCoeffs, R, T;

int fillObjp()
{
	for (int k = 0; k < CHECKERBOARD[1]; k++)
	{
		for (int j = 0; j < CHECKERBOARD[0]; j++)
		{
			objp.push_back(cv::Point3f(j, k, 0));
		}
	}
	return 0;
}

int calibrateCamera()
{
	int rms = cv::calibrateCamera(objpoints, imgpoints, cv::Size(frame.rows, frame.cols), cameraMatrix, distCoeffs, R, T);
	//std::cout << "cameraMatrix : " << cameraMatrix << std::endl;
	//std::cout << "distCoeffs : " << distCoeffs << std::endl;
	//std::cout << "Rotation vector : " << R << std::endl;
	//std::cout << "Translation vector : " << T << std::endl;
	//std::cout << "rms : " << rms << std::endl;
	return 0;
}

int saveParams()
{
	std::ofstream fout("D:/ÍÈÐ/UnityProject/New Unity Project/output.txt");
	if (!fout.is_open())
	{
		std::cerr << "Can't open output file!" << std::endl;
		exit(1);
	}
	fout << "cameraMatrix : " << cameraMatrix << std::endl;
	fout << "distCoeffs : " << distCoeffs << std::endl;
	
	return 0;
}

int getImages(Color32** raw, int width, int height, int numOfImg) //, bool isShow)
{
	frame = cv::Mat(height, width, CV_8UC4, raw);
	cvtColor(frame, frame, cv::COLOR_BGRA2BGR);
	flip(frame, frame, 0);
	i = numOfImg;
	if (numOfImg < numOfCalibFrames)
	{
		isCalibFrame = true;
	}
	if (numOfImg == 0)
	{
		fillObjp();
	}
	if (numOfImg == numOfCalibFrames)
	{
		calibrateCamera();
		saveParams();
	}
	return 0;
}

void processImage(unsigned char* data, int width, int height)
{
	//cv::Mat bgra_img;
	//cv::cvtColor(frame, bgra_img, cv::COLOR_RGB2BGRA);
	//cv::flip(frame, frame, 0);
	//cv::circle(argb_img, cv::Point(argb_img.cols / 2, argb_img.rows / 2), 100, cv::Scalar(255, 0, 0, 255), 10);
	/*std::vector<cv::Mat> bgra;
	split(argb_img, bgra);
	swap(bgra[0], bgra[3]);
	swap(bgra[1], bgra[2]);
	cv::Mat bgra_img;
	cv::merge(bgra, bgra_img);*/
	if (isCalibFrame)
	{
		std::cout << i << std::endl;
		cv::Mat gray;
		cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
		/*std::string path = "D:/ÍÈÐ/Calibration samples/image" + std::to_string(i) + ".jpg";
		cv::imwrite(path, gray);*/
		std::vector<cv::Point2f> corner_pts;
		bool success = cv::findChessboardCorners(gray, cv::Size(CHECKERBOARD[0], CHECKERBOARD[1]), corner_pts, cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FAST_CHECK | cv::CALIB_CB_NORMALIZE_IMAGE);
		if (success)
		{
			cv::TermCriteria criteria(cv::TermCriteria::Type::EPS | cv::TermCriteria::Type::MAX_ITER, 30, 0.001);

			cv::cornerSubPix(gray, corner_pts, cv::Size(11, 11), cv::Size(-1, -1), criteria);


			cv::drawChessboardCorners(frame, cv::Size(CHECKERBOARD[0], CHECKERBOARD[1]), corner_pts, success);
			objpoints.push_back(objp);
			imgpoints.push_back(corner_pts);
		}
		isCalibFrame = false;
	}
	cv::cvtColor(frame, frame, cv::COLOR_BGR2BGRA);
	flip(frame, frame, 0);
	memcpy(data, frame.data, frame.total() * frame.elemSize());
}