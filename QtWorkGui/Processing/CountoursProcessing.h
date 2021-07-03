#pragma once

#include <iostream>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <thread>

class CountoursProcessing
{
	std::vector<std::vector<cv::Point>> master_contours;
	std::vector<cv::Vec4i> master_hiararchy;
	int threshold;
	cv::Mat originalImgWithCounter;
public:
	CountoursProcessing();
	CountoursProcessing(const CountoursProcessing& drop);
	~CountoursProcessing();
	//CountoursProcessing(const CountoursProcessing &drop);
	void setThreshold(int const newThreshold);
	void findContours(cv::Mat const* inputImg, std::vector<std::vector<cv::Point>> &outContours, std::vector<cv::Vec4i> &outHiararchy);
	void findAndSetMasterContours(cv::Mat const* inputImg);
	void setMasterCounter(std::vector<std::vector<cv::Point>> const* inContours, std::vector<cv::Vec4i> const* inHiararchy);
	int setMasterCounter(cv::Rect rectROI);
	void setMasterCounter(cv::Mat imgROI);
	void changeContours(cv::Size const originalImageSize, std::vector<std::vector<cv::Point>>& inOutContours, std::vector<cv::Vec4i>& inOutHiararchy, std::vector<cv::Point> const maskPoint);
	void getMasterContours(std::vector<std::vector<cv::Point>>& outContours, std::vector<cv::Vec4i>& outHiararchy);
	void setMasterContours(std::vector<std::vector<cv::Point>> const *inContours, std::vector<cv::Vec4i> const *inHiararchy);
	void drawContours(cv::Mat const *inputImg, cv::Scalar color);
	cv::Mat getDrawContours(cv::Rect ROI);
};

void draw(cv::Mat *inOutputImg,std::vector<std::vector<cv::Point>> counters);
