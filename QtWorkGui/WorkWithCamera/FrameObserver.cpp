#include "FrameObserver.h"


void FrameObserver::FrameReceived(const AVT::VmbAPI::FramePtr pFrame)
{
	VmbFrameStatusType eReceiveStatus;
	if (VmbErrorSuccess == pFrame->GetReceiveStatus(eReceiveStatus))
	{
		if (VmbFrameStatusComplete == eReceiveStatus)
		{
			// Put your code here to react on a successfully received frame
			VmbUchar_t* pbuffer;
			VmbUint32_t w, h;

			pFrame->GetImage(pbuffer);
			pFrame->GetHeight(h);
			pFrame->GetWidth(w);

			QImage myImage = QImage(pbuffer, w, h, QImage::Format_Indexed8);
			QPixmap m_img = QPixmap::fromImage(myImage);

			cv::Mat bufer(h, w, CV_8UC1, pbuffer);
			cv::cvtColor(bufer, bufer, CV_GRAY2BGR);
			newFrame->updateMat(bufer, m_img);
			newFrame->setFlagImageIsNull(false);
			display->updateFrame();
			LOG.logMessege("new frame craded", _DEBUG_);
		}
		else
		{
			// Put your code here to react on an unsuccessfully received frame 
			//std::cout << "pnh";
		}
	}
	m_pCamera->QueueFrame(pFrame);
}


