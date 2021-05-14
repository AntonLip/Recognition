#include "myLabel.h"


myLabel::myLabel(QWidget *parent) :QLabel(parent)
{
	//this->setStyleSheet("background-color: red");
	_aspectRotMod = Qt::KeepAspectRatio;
	myPixmap_bufer = nullptr;
	myPixmap_mouve = nullptr;
	add = false;
	up_or_left = false;
	down_or_right = false;
	imgIsShow = false;
	imgScaled = 100;
	_scaled = new double[11]{0, 0.25, 0.5, 0.75, 1, 1.25, 1.5, 2, 3, 5};
	activ_scaled = 4;
	drPoint = QPoint(0, 0);
	original_drPoint == QPoint(0, 0);
	imageFormat = 0;
}


myLabel::~myLabel()
{
}

void myLabel::toImgCoordinate(int &inOutX, int &inOutY, bool isContains)
{
	if (scaledSize.width() > this->width())
	{
		inOutX += drPoint.x();
	}
	else
	{
		inOutX -= (this->width() - scaledSize.width()) / 2;
	}
	if (inOutX >= scaledSize.width() && isContains)
		inOutX = scaledSize.width()-1;
	else if (inOutX <= 0 && isContains)
		inOutX = 0;

	if (scaledSize.height() > this->height())
	{
		inOutY += drPoint.y();
	}
	else
	{
		inOutY -= (this->height() - scaledSize.height()) / 2;
	}

	if (inOutY > scaledSize.height()&& isContains)
		inOutY = scaledSize.height()-1;
	else if (inOutY < 0 && isContains)
		inOutY = 0;
}

void myLabel::toImgCoordinate_(int& inOutX, int& inOutY, bool isContains)
{
	double scal_H{ static_cast<double>(scaledSize.height()) / originalSize.height() };
	double scal_W{ static_cast<double>(scaledSize.width()) / originalSize.width() };
	
	if (scaledSize.width() > this->width())
	{
		inOutX = (drPoint.x() + inOutX) / scal_W;
	}
	else
	{
		inOutX = (inOutX - (this->width() - scaledSize.width()) / 2) / scal_W;
	}
	if (inOutX >= originalSize.width() && isContains)
		inOutX = originalSize.width() - 1;
	else if (inOutX <= 0 && isContains)
		inOutX = 0.0;

	if (scaledSize.height() > this->height())
	{
		inOutY = (drPoint.y() + inOutY) / scal_H;
	}
	else
	{
		inOutY = (inOutY - (this->height() - scaledSize.height()) / 2) / scal_H;
	}

	if (inOutY > originalSize.height() && isContains)
		inOutY = originalSize.height() - 1;
	else if (inOutY < 0 && isContains)
		inOutY = 0.0;
}

QPoint myLabel::getImageCoordinate(bool isContains)
{
	double scal_H{ static_cast<double>(scaledSize.height()) / originalSize.height() };
	double scal_W{ static_cast<double>(scaledSize.width()) / originalSize.width() };
	double x{ 0 }, y{ 0 };
	if (scaledSize.width() > this->width())
	{
		x = (drPoint.x() + x_labl) / scal_W;
	}
	else
	{
		x = (x_labl - (this->width() - scaledSize.width()) / 2) / scal_W;
	}
	if (x >= originalSize.width() && isContains)
		x = originalSize.width()-1;
	else if (x <= 0 && isContains)
		x = 0.0;

	if (scaledSize.height() > this->height())
	{
		y = (drPoint.y() + y_labl) / scal_H;
	}
	else
	{
		y =(y_labl -(this->height() - scaledSize.height())/2 ) / scal_H;
	}

	if (y > originalSize.height()&& isContains)
		y = originalSize.height()-1;
	else if (y < 0 && isContains)
		y = 0.0;
	return QPoint(x, y);
}

QPoint myLabel::getFirstImagePoint()
{
	return QPoint(f_x_pixMap,f_y_pixMap);
}

void myLabel::formatImage(int formatType)
{
	if (imageFormat == formatType)
	{

	}
	else
	{
		if (formatType == 0)
		{
			my_Pixmap = my_PixmapOriginal;
			//my_Pixmap = my_Pixmap.scaled(scaledSize);
			delete myPixmap_bufer;
			myPixmap_bufer = new QPixmap(my_Pixmap);
		}
		else if (formatType == 1)
		{
			QImage buferImg(my_Pixmap.toImage());
			buferImg = buferImg.convertToFormat(QImage::Format_Grayscale8);
			buferImg = buferImg.convertToFormat(QImage::Format_RGB32);
			delete myPixmap_bufer;
			myPixmap_bufer = new QPixmap(QPixmap::fromImage(buferImg));
			my_Pixmap = *myPixmap_bufer;
		}
		imageFormat = formatType;
	}
}

void myLabel::update_myPixmap(const QPixmap& img)
{
	my_Pixmap = img;
	my_PixmapOriginal = img;
	originalSize = my_PixmapOriginal.size();
	scaledSize = originalSize;
	scalCoef_W = static_cast<double>(this->width()) / originalSize.width();
	scalCoef_H = static_cast<double>(this->height()) / originalSize.height();
	delete myPixmap_bufer;
	myPixmap_bufer = new QPixmap(my_Pixmap);
	//delete myPixmap_mouve;
	//myPixmap_mouve = new QPixmap(my_Pixmap.copy(drPoint.x(), drPoint.y(), this->width(), this->height()));
	setAllImgScaled();
	this->scaledPixmap();
}

double myLabel::get_activScaled()
{
	if (activ_scaled<11 && activ_scaled>0)
	{
		return _scaled[activ_scaled] * 100;
	}
	else
	{
		return _scaled[11] * 100;
	}
}

void myLabel::set_myPixmap(const QPixmap* img)
{
	my_Pixmap = *img;
	my_PixmapOriginal = *img;
	originalSize = my_PixmapOriginal.size();
	scaledSize = originalSize;
	scalCoef_W = static_cast<double>(this->width()) / originalSize.width();
	scalCoef_H = static_cast<double>(this->height()) / originalSize.height();
	delete myPixmap_bufer;
	myPixmap_bufer = new QPixmap(my_Pixmap);
	this->setPixmap(*myPixmap_bufer);
	activ_scaled = 4;
	this->updateGeometry();
	setAllImgScaled();
}

QPixmap myLabel::myPixmap() const
{
	return my_Pixmap;
}

void myLabel::mouseMoveEvent(QMouseEvent *evnt)
{
	if (evnt->x() < 0)
	{
		x_labl = 0;
		emit mouseLeft();
	}
	else if (evnt->x() > this->width())
	{
		x_labl = this->width() - 1;
		emit mouseLeft();
	}
	else
	{
		x_labl = evnt->x();
	}

	if (evnt->y() < 0)
	{
		y_labl = 0;
		emit mouseLeft();
	}
	else if (evnt->y() > this->height())
	{
		y_labl = this->height() - 1;
		emit mouseLeft();
	}
	else
	{
		y_labl = evnt->y();
	}

	x_lablG = evnt->x();
	y_lablG = evnt->y();
	emit mousePos();
}

void myLabel::mousePressEvent(QMouseEvent *evnt)
{
	first_x_labl = evnt->x();
	first_y_labl = evnt->y();
	f_x_pixMap = first_x_labl;
	f_y_pixMap = first_y_labl;
	//toImgCoordinate(f_x_pixMap, f_y_pixMap);
	toImgCoordinate_(f_x_pixMap, f_y_pixMap);
	/*std::cout << "X " << f_x_pixMap << std::endl;
	std::cout << "Y " << f_y_pixMap << std::endl;*/
	//f_x_pixMap = f_x_labl + drPoint.x();
	//f_y_pixMap = f_y_labl + drPoint.y();
	//ref_x = evnt->x();
	//ref_y = evnt->y();
	add = true;
	emit mousePressed();
}

void myLabel::leaveEvent(QEvent *evnt)
{
	emit mouseLeft();
}

void myLabel::mouseReleaseEvent(QMouseEvent *evnt)
{
	//s_x_pixMap = evnt->x();
	//s_y_pixMap = evnt->y()-this->y();
	add = false;
	up_or_left = false;
	down_or_right = false;
	emit mouseRelease();
}

void myLabel::reset_x_y()
{
	//f_x_labl = 0;
	//f_y_labl = 0;
	//s_x_labl = 0;
	//s_y_labl = 0;
}

void myLabel::add_rect(QRect &Input, QPen newPen)
{
	if (add == true)
	{
		toImgCoordinate(x_labl, y_labl);
		Input.setRect(f_x_pixMap, f_y_pixMap, x_labl - f_x_pixMap, y_labl- f_y_pixMap);
		this->draw_rect(&QtRotateRect(Input), newPen);
		this->show_partImg(drPoint.x(), drPoint.y(), this->width(), this->height());
	}
}

void myLabel::show_roi(std::vector <QRect> &Input)
{
	delete myPixmap_bufer;
	myPixmap_bufer = new QPixmap(my_Pixmap);
	QPainter *p = new QPainter(myPixmap_bufer);
	p->setPen(QPen(Qt::red, 1, Qt::DashLine));
	for (int i{ 0 }; i < Input.size(); i++)
		p->drawRect(Input[i]);
	this->setPixmap(*myPixmap_bufer);
	delete p;
}

void myLabel::draw_rect(QtRotateRect* Input, QPen newPen)
{
	if (imgIsShow)
	{
		delete myPixmap_bufer;
		myPixmap_bufer = new QPixmap(my_Pixmap);
		imgIsShow = false;
	}
	else
	{

	}
	QPainter* p = new QPainter(myPixmap_bufer);
	p->setPen(newPen);
	p->drawLine(QPoint(Input->getUpLeft_X(), Input->getUpLeft_Y()), QPoint(Input->getUpRigth_X(), Input->getUpRigth_Y()));
	p->drawLine(QPoint(Input->getDownLeft_X(), Input->getDownLeft_Y()), QPoint(Input->getDownRigth_X(), Input->getDownRigth_Y()));
	p->drawLine(QPoint(Input->getDownLeft_X(), Input->getDownLeft_Y()), QPoint(Input->getUpLeft_X(), Input->getUpLeft_Y()));
	p->drawLine(QPoint(Input->getDownRigth_X(), Input->getDownRigth_Y()), QPoint(Input->getUpRigth_X(), Input->getUpRigth_Y()));
	delete p;
}

void myLabel::draw_circle(QPoint* centerPoint, int radius, QPen newPen)
{
	if (imgIsShow)
	{
		delete myPixmap_bufer;
		myPixmap_bufer = new QPixmap(my_Pixmap);
		imgIsShow = false;
	}
	else
	{

	}
	QPainter* p = new QPainter(myPixmap_bufer);
	p->setPen(newPen);
	p->drawEllipse(*centerPoint,radius,radius);
	delete p;
}

void myLabel::draw_picture(cv::Mat drawPicture,QRect limitRect)
{
	if (imgIsShow)
	{
		delete myPixmap_bufer;
		myPixmap_bufer = new QPixmap(my_Pixmap);
		imgIsShow = false;
	}
	else
	{

	}
	QImage drPic(drawPicture.data, drawPicture.cols, drawPicture.rows, drawPicture.step, QImage::Format::Format_BGR888);
	if (limitRect.width() != 0)
		drPic=drPic.scaled(limitRect.width(), limitRect.height());
	QPainter* p = new QPainter(myPixmap_bufer);
	p->drawImage(limitRect.topLeft(),drPic);
	delete p;
}

void myLabel::show_roi(std::vector<QRect> &Input, std::vector<int> rect, int circle)
{
	delete myPixmap_bufer;
	myPixmap_bufer = new QPixmap(my_Pixmap);
	QPainter *p = new QPainter(myPixmap_bufer);
	p->setPen(QPen(Qt::red, 1, Qt::DashLine));
	for (int i{ 0 }; i < rect.size(); i++)
		p->drawRect(Input[rect[i]]);
	this->setPixmap(*myPixmap_bufer);
	delete p;
}

void myLabel::set_rect(std::vector<QRect> &InOutput)
{
	//InOutput.push_back(QRect(QPoint(f_x_labl, f_y_labl), QPoint(s_x_labl, s_y_labl)));
	add = false;
}

void myLabel::show_partImg(int dx, int dy, int width, int height)
{
	this->repaint();
	if (dx < 0)
		dx = 0;
	else if (dx >= (scaledSize.width() - width))
		dx = scaledSize.width() - width;
	if (dy < 0)
		dy = 0;
	else if (dy >= (scaledSize.height() - height))
		dy = scaledSize.height() - height;

	drPoint.setX(dx);
	drPoint.setY(dy);
	bool notScaled{ false };
	double bufer_scalCoef_W{ static_cast<double>(originalSize.width()) / scaledSize.width() };
	if (bufer_scalCoef_W >= 1.0)
	{
		//bufer_scalCoef_W = 1.0;
	}
	//else
	{
		dx = dx * bufer_scalCoef_W;
		bufer_scalCoef_W *= scalCoef_W;
	}
	double bufer_scalCoef_H{ static_cast<double>(originalSize.height()) / scaledSize.height() };
	if (bufer_scalCoef_H >= 1.0)
	{
		//notScaled = true;
		//bufer_scalCoef_H = 1.0;
	}
	//else*/
	{
		dy = dy * bufer_scalCoef_H;
		bufer_scalCoef_H *= scalCoef_H;
	}
	//double needed_W{this->width}

	delete myPixmap_mouve;
	if (myPixmap_bufer == nullptr)
	{
		myPixmap_mouve = new QPixmap(my_Pixmap.copy(dx, dy, originalSize.width()*bufer_scalCoef_W, originalSize.height()*bufer_scalCoef_H));
	}
	else
	{
		myPixmap_mouve = new QPixmap(myPixmap_bufer->copy(dx, dy, originalSize.width() * bufer_scalCoef_W, originalSize.height() * bufer_scalCoef_H));
		//myPixmap_mouve = new QPixmap(myPixmap_bufer->copy(dx, dy, width, height));
	}
	
	int scaledMouvePixmap{ 0 };
	if (scaledSize.width() <= this->width())
		scaledMouvePixmap = 10;
	if (scaledSize.height() <= this->height())
		++scaledMouvePixmap;
	QSize qwe(myPixmap_mouve->size());
	if (scaledMouvePixmap == 0)
	{
		//if (!notScaled)
			this->setPixmap(myPixmap_mouve->scaled(this->size(), _aspectRotMod));
		//else
		//	this->setPixmap(*myPixmap_mouve);
	}
	else if (scaledMouvePixmap == 10)
		this->setPixmap(myPixmap_mouve->scaled(QSize(this->scaledSize.width(), this->height()), _aspectRotMod));
	else if (scaledMouvePixmap == 1)
		this->setPixmap(myPixmap_mouve->scaled(QSize(this->width(), this->scaledSize.height()), _aspectRotMod));
	else if (scaledMouvePixmap == 11)
	{
		//_aspectRotMod = Qt::IgnoreAspectRatio;
		this->setPixmap(myPixmap_mouve->scaled(this->scaledSize, _aspectRotMod));
		scaledSize = pixmap()->size();
	}
	imgIsShow = true;
}

void myLabel::show_partImg()
{
	this->repaint();
	int dx{ drPoint.x() };
	int dy{ drPoint.y() };

	double bufer_scalCoef_W{ static_cast<double>(originalSize.width()) / scaledSize.width() };
	if (bufer_scalCoef_W >= 1.0)
	{
		//bufer_scalCoef_W = 1.0;
	}
	//else
	{
		dx = dx * bufer_scalCoef_W;
		bufer_scalCoef_W *= scalCoef_W;
	}
	double bufer_scalCoef_H{ static_cast<double>(originalSize.height()) / scaledSize.height() };
	if (bufer_scalCoef_H >= 1.0)
	{
		//bufer_scalCoef_H = 1.0;
	}
	//else
	{
		dy = dy * bufer_scalCoef_H;
		bufer_scalCoef_H *= scalCoef_H;
	}
	//double needed_W{this->width}

	delete myPixmap_mouve;
	if (myPixmap_bufer == nullptr)
	{
		myPixmap_mouve = new QPixmap(my_Pixmap.copy(dx, dy, originalSize.width() * bufer_scalCoef_W, originalSize.height() * bufer_scalCoef_H));
	}
	else
	{
		myPixmap_mouve = new QPixmap(myPixmap_bufer->copy(dx, dy, originalSize.width() * bufer_scalCoef_W, originalSize.height() * bufer_scalCoef_H));
		//myPixmap_mouve = new QPixmap(myPixmap_bufer->copy(dx, dy, width, height));
	}
	int scaledMouvePixmap{ 0 };
	if (scaledSize.width() <= this->width())
		scaledMouvePixmap = 10;
	if (scaledSize.height() <= this->height())
		++scaledMouvePixmap;
	if (scaledMouvePixmap == 0)
	{
		this->setPixmap(myPixmap_mouve->scaled(this->size(), _aspectRotMod));
	}
	else if (scaledMouvePixmap == 10)
		this->setPixmap(myPixmap_mouve->scaled(QSize(this->scaledSize.width(), this->height()), _aspectRotMod));
	else if (scaledMouvePixmap == 1)
		this->setPixmap(myPixmap_mouve->scaled(QSize(this->width(), this->scaledSize.height()), _aspectRotMod));
	else if (scaledMouvePixmap == 11)
	{
		//_aspectRotMod = Qt::IgnoreAspectRatio;
		this->setPixmap(myPixmap_mouve->scaled(this->scaledSize, _aspectRotMod));
		scaledSize = pixmap()->size();
	}
	imgIsShow = true;
}

double myLabel::scaledPixmap(int scaled, int &dx, int &dy)
{
	bool ver_center{ false };
	bool hor_center{ false };
	if (scaledSize.width() < this->width())
		hor_center = true;
	if (scaledSize.height() < this->height())
		ver_center=true;
	//Qt::AspectRatioMode _aspectRotMod;
	if (scaled == 0 && activ_scaled == 0)
	{
		activ_scaled = 0;
		scaledSize.setWidth(this->width());
		scaledSize.setHeight(this->height());
		_aspectRotMod = Qt::KeepAspectRatio;
	}
	else
	{
		if (activ_scaled != 0)
		{

			if (scaled != 0)
			{
				this->toCenterPoint(drPoint);
				original_drPoint.setX(drPoint.x() / _scaled[activ_scaled]);
				original_drPoint.setY(drPoint.y() / _scaled[activ_scaled]);
				if (scaled > 0 && activ_scaled < 10)
				{
					activ_scaled++;
				}
				else if (scaled < 0 && activ_scaled>1)
				{
					activ_scaled--;
				}
				scaledSize.setWidth(originalSize.width() * _scaled[activ_scaled]);
				scaledSize.setHeight(originalSize.height() * _scaled[activ_scaled]);
				_aspectRotMod = Qt::IgnoreAspectRatio;
			}
			else
			{
				activ_scaled = 0;
				scaledSize.setWidth(this->width());
				scaledSize.setHeight(this->height());
				_aspectRotMod = Qt::KeepAspectRatio;
			}
		}
		else
		{
			this->toCenterPoint(drPoint);
			original_drPoint.setX(drPoint.x() / (static_cast<double>(scaledSize.width())/originalSize.width()));
			original_drPoint.setY(drPoint.y() / (static_cast<double>(scaledSize.height()) / originalSize.height()));
			if (scaled > 0)
				activ_scaled = max_activ_scaled;
			else
				activ_scaled = min_activ_scaled;
			scaledSize.setWidth(originalSize.width() * _scaled[activ_scaled]);
			scaledSize.setHeight(originalSize.height() * _scaled[activ_scaled]);
			/*original_drPoint.setX(scaledSize.width() * _scaled[activ_scaled]);
			original_drPoint.setY(scaledSize.height() * _scaled[activ_scaled]);*/
			_aspectRotMod = Qt::IgnoreAspectRatio;
		}
	}
	if (myPixmap_bufer != nullptr)
	{
		//QPixmap scaledPixmap;
		//scaledPixmap = my_PixmapOriginal.scaled(scaledSize, _aspectRotMod);
		//delete myPixmap_bufer;
		//myPixmap_bufer = new QPixmap(scaledPixmap);
		//my_Pixmap = scaledPixmap;
		int buferFormat{ imageFormat };
		imageFormat = 0;
		formatImage(buferFormat);
		//scaledSize.setHeight(scaledPixmap.height());
		//scaledSize.setWidth(scaledPixmap.width());
		if (activ_scaled != 0)
		{
			if (!hor_center)
				dx = original_drPoint.x() * _scaled[activ_scaled];
			else
				dx = scaledSize.width() / 2;
			if (!ver_center)
				dy = original_drPoint.y() * _scaled[activ_scaled];
			else
				dy = scaledSize.height()/2;
			this->toUpLeftpoint(dx, dy);
		}
		else
		{

		}
	}
	
	if (scaled != 0)
	{
		return _scaled[activ_scaled] * 100;
	}
	else
	{
		return _scaled[11] * 100;
	}
}

void myLabel::scaledPixmap()
{
	//Qt::AspectRatioMode _aspectRotMod;

	this->toCenterPoint(drPoint);
	original_drPoint.setX(drPoint.x() / _scaled[activ_scaled]);
	original_drPoint.setY(drPoint.y() / _scaled[activ_scaled]);

	this->toUpLeftpoint(drPoint);

	if (activ_scaled == 0)
	{
		scaledSize.setWidth(width());
		scaledSize.setHeight(height());
	}
	else
	{
		scaledSize.setWidth(originalSize.width() * _scaled[activ_scaled]);
		scaledSize.setHeight(originalSize.height() * _scaled[activ_scaled]);
	}

	_aspectRotMod = Qt::IgnoreAspectRatio;
	if (myPixmap_bufer != nullptr)
	{
		//QPixmap scaledPixmap;
		//scaledPixmap = my_PixmapOriginal.scaled(scaledSize, _aspectRotMod);
		//delete myPixmap_bufer;
		//myPixmap_bufer = new QPixmap(scaledPixmap);
		//my_Pixmap = scaledPixmap;
		int buferFormat{ imageFormat };
		imageFormat = 0;
		formatImage(buferFormat);
		//scaledSize.setHeight(scaledPixmap.height());
		//scaledSize.setWidth(scaledPixmap.width());
	}
}

void myLabel::moveImg(int &out_dx, int &out_dy)
{
	int dx{first_x_labl-x_labl};
	first_x_labl = x_labl;
	int dy{ first_y_labl - y_labl };
	first_y_labl = y_labl;
	out_dx = drPoint.x() + dx;
	out_dy = drPoint.y() + dy;
}

void myLabel::getDrPoint(int &x, int &y)
{
	x = drPoint.x();
	y = drPoint.y();
}

void  myLabel::getMaxMinScal(int &max, int &min)
{
	max = max_activ_scaled;
	min = min_activ_scaled;
}

void myLabel::toCenterPoint(QPoint &upLeftPoint)
{
	//if(this->width()<scaledSize.width())
		upLeftPoint.setX(upLeftPoint.x() + (this->width()-1) / 2);
	/*else
		upLeftPoint.setX( (this->width() - 1) / 2);*/
	//if(this->height()<scaledSize.height())
		upLeftPoint.setY(upLeftPoint.y() + (this->height()-1) / 2);
	/*else
		upLeftPoint.setX((this->height() - 1) / 2);*/
}

void myLabel::toUpLeftpoint(QPoint &centerPoint)
{
	centerPoint.setY(centerPoint.y() - (this->height() - 1) / 2);
	/*if (centerPoint.y() < 0)
		centerPoint.setY(0);*/
	centerPoint.setX(centerPoint.x() - (this->width() - 1) / 2);
	/*if (centerPoint.x() < 0)
		centerPoint.setY(0);*/
}

void myLabel::toUpLeftpoint(int &x, int &y)
{
	y = y - (this->height() - 1) / 2;
	x = x - (this->width() - 1) / 2;
}

void myLabel::resizeEvent(QResizeEvent* event)
{
	oldSize = event->oldSize();
	scalCoef_W = static_cast<double>(this->width()) / originalSize.width();
	scalCoef_H = static_cast<double>(this->height()) / originalSize.height();
}

QPoint*  myLabel::getImgPoint(void)
{
	return &(QPoint(x_labl, y_labl));
}

QSize myLabel::getOldSize()
{
	return oldSize;
}

QSize* myLabel::getScaledImgSize()
{
	return &scaledSize;
}

QSize* myLabel::getOriginalImgSize()
{
	return &originalSize;
}

void myLabel::setAllImgScaled()
{
	double scal_NormImg{ (double)this->width() / (double)originalSize.width() };
	_scaled[11] = scal_NormImg;
	for (int i{ 0 }; i < 9; i++)
	{
		if (_scaled[i] > scal_NormImg)
		{
			max_activ_scaled = i;
			i = 10;
		}
		else
			max_activ_scaled = 10;
	}
	for (int i{ 9 }; i >= 0; i--)
	{
		if (_scaled[i] < scal_NormImg)
		{
			min_activ_scaled = i;
			i = -1;
		}
		else
			min_activ_scaled = 0;
	}
}

void myLabel::getPointInImg(int& x, int& y)
{
	x = x_labl;
	y = y_labl;
	toImgCoordinate(x,y);
}

void myLabel::setFirstPixmapPoint(QPoint newPoint)
{
	f_x_pixMap = newPoint.x();
	f_y_pixMap = newPoint.y();
}

QPixmap myLabel::getPixmapWithROI(std::vector<QRect> &Input) const
{
	QPixmap out{my_PixmapOriginal};
	QPainter *p = new QPainter(&out);
	p->setPen(QPen(Qt::red, 1, Qt::DashLine));
	for (int i{ 0 }; i < Input.size(); i++)
		p->drawRect(Input[i]);
	delete p;
	return out;
}

double round(double InputNumber, int const accuracy)
{
	InputNumber *= pow(10, accuracy + 1);
	InputNumber = static_cast<int>(round(InputNumber));
	return static_cast<double>(InputNumber / pow(10, accuracy));
}