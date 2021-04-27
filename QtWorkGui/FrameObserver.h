#pragma once
#include "VimbaCPP.h"
//#include "D:\soft\VimbaCPP\VimbaCPP\Include\IFrameObserver.h"
#include <VimbaCPP/Include/IFrameObserver.h>
#include "iostream"
#include <opencv2/opencv.hpp>
#include <qimage.h>

#include "ProcessedObj.h"

#include "QtGuiDisplay.h"
#include "ui_GE_Widget.h"
#include "simplLoger.h"

using namespace AVT;
using namespace VmbAPI;
using namespace cv;

class FrameObserver : public IFrameObserver
{
private:
	 QtGuiDisplay *display;
	 //Ui::GE_WidgetClass m_ui_ge;
	 //QImage myImage; //переменная,хранящая кадр с камеры
	 //QPixmap m_img;
	 VmbUchar_t* pbuffer;
	 VmbUint32_t w, h;
	 ProcessedObj* newFrame;


public:
	FrameObserver(CameraPtr pCamera, QtGuiDisplay* videaDisplay, ProcessedObj *loadObj0) : IFrameObserver(pCamera), display(videaDisplay), newFrame(loadObj0)
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
		 //delete pbuffer;
		 //delete newFrame;
	 }
};

