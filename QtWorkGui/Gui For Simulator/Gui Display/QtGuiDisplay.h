#pragma once

#include <QWidget>
#include "ui_QtGuiDisplay.h"
#include <QTime>
#include "qfiledialog.h"
#include "myLabel.h"
#include "Processing Object/ProcessedObject.h"
//#include "QtAreaToProcessed.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <cmath>

class QtGuiDisplay : public QWidget
{
	Q_OBJECT

	int delayUpdateFrame;;
	QTime *updateImageTime;
	cv::Mat tempImg;
	QPixmap TempPixmap;
	QCursor myCursor;
	std::vector<QRect> roi;

	//ProcessedObj *activProcessedObj;
	ProcessedObject* activProcessedObj;
	//QString dir_for_saveImg;
	//QString fileName;
	int activ_roi;
	int activProcesArea;
	bool change_roi;
	bool event_img;
	bool activatedRoi;
	bool activ;
	bool changesProcesedArearsGeometry;
	bool changeActivArea;
	void resizeEvent(QResizeEvent* event);
	//bool addNewBrigthnesRect;
	double activ_scaled;
	double hor_scaled;
	double vert_scaled;
	bool setObj;
	bool isProcessingActiv;
	bool isZoomNow;
	void setCursor_àorChangesTopBotton(double rotateAngel);
	void setCursor_àorChangesRightLeft(double rotateAngel);
	void setCursor_àorChangesTopRight_BottonLeft(double rotateAngel);
	void setCursor_àorChangesTopLeft_BottonRight(double rotateAngel);
public:
	QtGuiDisplay(QWidget *parent = Q_NULLPTR);
	~QtGuiDisplay();
	void setSizeScrollBar();
	//void setActivProcessObj(ProcessedObj &activObj, bool master=true, int number=0);
	void setActivProcessObj(ProcessedObject &activObj, bool master=true, int number=0);
	void setEanbleActivededRoi(bool activ);
	void setEnableWidtsGrouBox(bool enable);
	void setActiv(bool activ);
	void setChangeActivArea(bool isChange);
	void addBrightnesCorrectRect(bool isAdd);
	void setChangesProcessedArears(bool isChang);
	//void processedAreaScale(QtProcessedArea &InOutArea ,bool toOriginalScal=false);
	void draw_proceseArears();
	void add_rect(int procesType);
	void add_circle();
	void changeAreaType(int newType, QtProcessedArea &InOutArea);
	QRect getLabelRect();
	void changeImgFormat(int formatType);
	//void mouseReleaseEvent(QMouseEvent* evnt);
	bool isActiv();
	bool getChageActivArea();
	bool ProcessedIsActiv();
	void updateFrame();
	//ProcessedObj* getActivObject();
	void setProcessObjStatus(bool isMaster);//0-Live 1-Master;
	void updateProcessObj(ProcessedObject& activObj);
	void setActivProcesArea(int activArea);
	int getDelayUpdateFrame();
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
	void slot_resetAngel(int activRect);
	void slot_changeProcssActiv(int isActiv); //0-disenable 1-enable
	void slot_updateTrigerDelay(int newDelay);
	void slot_delUpdateImageTime();
signals:
	void brightnesCorrectRectSet(bool isSet);
	void clic_pb();
	void changeActivProcesArea(int newActiv);
	void angelIsReset(int isReset);
	void signal_updateFrame();
	void getActivProcessArea();
};
