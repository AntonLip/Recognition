#include "FrameObserver.h"


void FrameObserver::FrameReceived(const FramePtr pFrame)
{
	VmbFrameStatusType eReceiveStatus;
	if (VmbErrorSuccess == pFrame->GetReceiveStatus(eReceiveStatus))
	{
		if (VmbFrameStatusComplete == eReceiveStatus)
		{
			// Put your code here to react on a successfully received frame
			pFrame->GetImage(pbuffer);
			
			pFrame->GetHeight(h);
			pFrame->GetWidth(w);

			QImage myImage = QImage(pbuffer, w, h, QImage::Format_Indexed8);
			QPixmap m_img = QPixmap::fromImage(myImage);

			cv::Mat bufer(h, w, CV_8UC1, pbuffer);
			cv::cvtColor(bufer, bufer, CV_GRAY2BGR);
			newFrame->SetObjParams("sensor live.jpg", "", bufer, m_img, false);
			display->updateFrame();
			LOG.logMessege("new frame craded", _DEBUG_);
			/*if (m_gewidget)
			{*/
				//m_ui_ge.label->setPixmap(m_img); //вывод кадра в лэйбл
				//if (m_makePhoto)//установка фона для сцены
				//{
				//	//img.save("background.jpg");
				//	m_ui_ge.widget->setSceneBackground(m_img);
				//	m_makePhoto = false;
				//	//qDebug() << "hello";
				//}
			/*}
			else
			{*/
				//m_ui.label_3->setPixmap(m_img);
				
				/*m_ui.linEdit_fileName->setText("Camera Vido");
				m_ui.comboBox_program->setItemIcon(1, QPixmap());*/
			//}
		}
		else
		{
			// Put your code here to react on an unsuccessfully received frame 
			//std::cout << "pnh";
		}
	}
	m_pCamera->QueueFrame(pFrame);
}


