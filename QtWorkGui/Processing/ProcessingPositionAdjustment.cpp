#include "ProcessingPositionAdjustment.h"

ProcessingPositionAdjustment::ProcessingPositionAdjustment()
{
	countorsProcessing_ = new ProcessingCountours();
}

ProcessingPositionAdjustment::ProcessingPositionAdjustment(const ProcessingPositionAdjustment& drop):
	comparrisImage_{drop.comparrisImage_},
	masterImage_(drop.masterImage_),
	processingImage_{ drop.processingImage_ },
	deltaAngel_{drop.deltaAngel_},
	deltsX_{drop.deltsX_},
	deltaY_{drop.deltaY_}
{
	if(drop.countorsProcessing_!=nullptr)
		countorsProcessing_ = new ProcessingCountours(*drop.countorsProcessing_);
}
