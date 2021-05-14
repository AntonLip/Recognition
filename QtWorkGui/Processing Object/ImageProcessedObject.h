#pragma once
#include "ProcessedObject.h"
#include "QtProcessedArea.h"

class ImageProcessedObject :
    protected ProcessedObject
{
protected:
    bool imageIsNull;
    std::vector<QtProcessedArea> processAreas;
};

