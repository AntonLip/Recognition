#pragma once

#include <QWidget>
#include "ui_QtGuiDisplay.h"
#include "qfiledialog.h"
#include "myLabel.h"
#include "QtAreaToProcessed.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <cmath>

class QtGuiDisplay : public QWidget
{
	Q_OBJECT

	cv::Mat tempImg;
	QPixmap TempPixmap;
	QCursor myCursor;
	std::vector<QRect> roi;
	ProcessedObj *activProcessedObj;
	//QString dir_for_saveImg;
	//QString fileName;
	int activ_roi;
	bool change_roi;
	bool event_img;
	bool activatedRoi;
	bool activ;
	bool changesProcesedArears;
	bool changeActivArea;
	void resizeEvent(QResizeEvent* event);
	bool addNewBrigthnesRect;
	double activ_scaled;
	double hor_scaled;
	double vert_scaled;
public:
	QtGuiDisplay(QWidget *parent = Q_NULLPTR);
	~QtGuiDisplay();
	void setSizeScrollBar();
	void setActivProcessObj(ProcessedObj *activObj, bool master=true, int number=0);
	void setEanbleActivededRoi(bool activ);
	void setEnableWidtsGrouBox(bool enable);
	void setActiv(bool activ);
	void setChangeActivArea(bool isChange);
	void addBrightnesCorrectRect(bool isAdd);
	void setChangesProcessedArears(bool isChang);
	void processedAreaScale(QtProcessedArea &InOutArea ,bool toOriginalScal=false);
	void draw_proceseArears();
	void add_rect(int procesType);
	void add_circle();
	void changeAreaType(int newType, QtProcessedArea &InOutArea);
	QRect getLabelRect();
	
	//void mouseReleaseEvent(QMouseEvent* evnt);
	bool isActiv();
	bool getChageActivArea();
private:
	Ui::QtGuiDisplay ui;

public slots:
	//void dataFromMainMenu(cv::Mat tempImg_out, QString fileName_in);
	void slot_mouvePixmap();
	void slot_mouseCurrentPos();
	void slot_mousePressed();
	void slot_mouseLeft();
	void slot_mouseLeft(int direct);
	void slot_mouseRelease();
	void slot_ZoomImg_In();
	void slot_ZoomImg_Out();
	void slot_ZoomImg_AllLabl();
	void slot_SetDirToSave();
	void slot_saveImg();
	void slot_reNameImg(QString newFileName);
	void slot_brighAreaDel();
	void updateImg();
signals:
	void brightnesCorrectRectSet(bool isSet);
	void clic_pb();
	void changeActivProcesArea(int newActiv);

};
