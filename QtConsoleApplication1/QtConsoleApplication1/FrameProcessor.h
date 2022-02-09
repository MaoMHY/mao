#ifndef FRAMEPROCESSOR_H
#define FRAMEPROCESSOR_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class FrameProcessor
{
public:
	virtual void process(cv::Mat &input, cv::Mat &output) = 0;
};

#endif // FRAMEPROCESSOR_H