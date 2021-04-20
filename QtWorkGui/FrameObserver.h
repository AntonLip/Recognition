#pragma once
#include "VimbaCPP.h"
//#include "D:\soft\VimbaCPP\VimbaCPP\Include\IFrameObserver.h"
#include <VimbaCPP/Include/IFrameObserver.h>
#include "iostream"
#include <opencv2/opencv.hpp>
#include <qimage.h>

#include "ProcessedObj.h"

#include "ui_QtGuiSimulator.h"
#include "ui_GE_Widget.h"

using namespace AVT;
using namespace VmbAPI;
using namespace cv;

class FrameObserver : public IFrameObserver
{
private:
	 Ui::QtGuiSimulator m_ui;
	 Ui::GE_WidgetClass m_ui_ge;
	 QImage myImage; //переменная,хранящая кадр с камеры
	 QPixmap m_img;
	 VmbUchar_t* pbuffer;
	 VmbUint32_t w, h;
	 ProcessedObj* m_loadObj;
	 bool m_makePhoto;
	 bool m_gewidget = false;

public:
	FrameObserver(CameraPtr pCamera, Ui::QtGuiSimulator&ui, QPixmap &img, bool &makePhoto, ProcessedObj *loadObj0) : IFrameObserver(pCamera), m_ui(ui), m_img(img), m_makePhoto(makePhoto), m_loadObj(loadObj0)
	{

	};
	FrameObserver(CameraPtr pCamera, Ui::GE_WidgetClass& ui, QPixmap& img, bool& makePhoto) : IFrameObserver(pCamera), m_ui_ge(ui), m_img(img), m_makePhoto(makePhoto)
	{
		m_gewidget = true;
	};

	FrameObserver(FrameObserver &f) : IFrameObserver(f)
	{

	};

	 void FrameReceived(const FramePtr pFrame) override;

	 ~FrameObserver()
	 {
		 delete pbuffer;
		 delete m_loadObj;
	 }
};

