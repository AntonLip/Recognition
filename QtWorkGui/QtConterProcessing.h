#pragma once

#include <QObject>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

class QtConterProcessing : public QObject
{
	Q_OBJECT
	std::vector<std::vector<cv::Point>> master_contours;
	std::vector<cv::Vec4i> master_hiararchy;
	int threshold;
	cv::Mat originalImgWithCounter;
public:
	QtConterProcessing(QObject *parent=nullptr);
	//QtConterProcessing(const QtConterProcessing& drob);
	//QtConterProcessing& operator =(const QtConterProcessing& drob);
	~QtConterProcessing();
	void setThreshold(int const newThreshold);
	void findContours(cv::Mat const* inputImg, std::vector<std::vector<cv::Point>>& outContours, std::vector<cv::Vec4i>& outHiararchy);
	void findAndSetMasterContours(cv::Mat const* inputImg);
	void setMasterCounter(std::vector<std::vector<cv::Point>> const* inContours, std::vector<cv::Vec4i> const* inHiararchy);
	int setMasterCounter(cv::Rect rectROI);
	void setMasterCounter(cv::Mat imgROI);
	void changeContours(cv::Size const originalImageSize, std::vector<std::vector<cv::Point>>& inOutContours, std::vector<cv::Vec4i>& inOutHiararchy, std::vector<cv::Point> const maskPoint);
	void getMasterContours(std::vector<std::vector<cv::Point>>& outContours, std::vector<cv::Vec4i>& outHiararchy);
	void setMasterContours(std::vector<std::vector<cv::Point>> const* inContours, std::vector<cv::Vec4i> const* inHiararchy);
	void drawContours(cv::Mat const* inputImg, cv::Scalar color);
	cv::Mat getDrawContours(cv::Rect ROI);
};
