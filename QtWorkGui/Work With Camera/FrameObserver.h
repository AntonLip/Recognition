#pragma once
#include "VimbaCPP.h"
//#include "D:\soft\VimbaCPP\VimbaCPP\Include\IFrameObserver.h"
#include <VimbaCPP/Include/IFrameObserver.h>
#include "iostream"
#include <opencv2/opencv.hpp>
#include <qimage.h>

#include "Processing Object/ProcessedObjectSensor.h"

#include "Gui For Simulator/Gui Display/QtGuiDisplay.h"
//#include "ui_GE_Widget.h"
#include "Loger/simplLoger.h"

using namespace AVT;
using namespace VmbAPI;
using namespace cv;

class FrameObserver : public IFrameObserver
{
private:
	 QtGuiDisplay *display;
	 ProcessedObjectSensor* newFrame;


public:
	FrameObserver(CameraPtr pCamera, QtGuiDisplay* videaDisplay, ProcessedObjectSensor *loadObj0) : IFrameObserver(pCamera), display(videaDisplay), newFrame(loadObj0)
	{

	};
	/*FrameObserver(CameraPtr pCamera, Ui::GE_WidgetClass& ui, QPixmap& img, bool& makePhoto) : IFrameObserver(pCamera), m_makePhoto(makePhoto)
	{
		m_gewidget = true;
	};*/

	FrameObserver(FrameObserver &f) : IFrameObserver(f)
	{

	};

	 void FrameReceived(const FramePtr pFrame) override;

	 ~FrameObserver()
	 {
		 LOG.logMessege("Frame obser destr", _INFO_);
	 }
};

