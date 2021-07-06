#pragma once
#include "VimbaCPP.h"
#include <VimbaCPP/Include/IFrameObserver.h>
#include "iostream"
#include <opencv2/opencv.hpp>
#include <qimage.h>

#include "ProcessingObject/ProcessedObjectSensor.h"

#include "GuiForSimulator/GuiDisplay/QtGuiDisplay.h"
#include "Loger/simplLoger.h"

using namespace cv;

class FrameObserver : public AVT::VmbAPI::IFrameObserver
{
private:
	 QtGuiDisplay *display;
	 ProcessedObjectSensor* newFrame;


public:
	FrameObserver(AVT::VmbAPI::CameraPtr pCamera, QtGuiDisplay* videaDisplay, ProcessedObjectSensor *loadObj0) : IFrameObserver(pCamera), display(videaDisplay), newFrame(loadObj0)
	{

	};
	/*FrameObserver(CameraPtr pCamera, Ui::GE_WidgetClass& ui, QPixmap& img, bool& makePhoto) : IFrameObserver(pCamera), m_makePhoto(makePhoto)
	{
		m_gewidget = true;
	};*/

	FrameObserver(FrameObserver &f) : IFrameObserver(f)
	{

	};

	 void FrameReceived(const AVT::VmbAPI::FramePtr pFrame) override;

	 ~FrameObserver()
	 {
		 LOG.logMessege("Frame obser destr", _INFO_);
	 }
};
