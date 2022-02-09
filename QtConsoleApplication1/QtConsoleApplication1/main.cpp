#include <QtCore/QCoreApplication>
#include "VideoProcessor.h"
#include <opencv2\opencv.hpp>
//#include "stdafx.h"

using namespace cv;
using namespace std;


void detect(Mat& img, Mat& out)
{
	//namedWindow("Camera");
	// 先要把每帧图像转化为灰度图
	cvtColor(img, out, CV_BGR2GRAY);
	equalizeHist(out, out);
	CascadeClassifier faces_cascade;
	faces_cascade.load("F:\\opencv455\\opencv\\sources\\data\\haarcascades_cuda\\haarcascade_frontalface_alt.xml");
	vector<Rect> faces;
	faces_cascade.detectMultiScale(out, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
	for (int i = 0; i < faces.size(); i++) {
		Rect roi = faces[i];
		rectangle(out, cvPoint(roi.x, roi.y), cvPoint(roi.x + roi.width, roi.y + roi.height), cvScalar(0.0, 255));
		//imwrite("C:\\Users\\DELL\\Desktop\\face.jpg", img(roi));
		//imshow("Camera", img);
		//waitKey(0);
	}
	// 对像素进行翻转
	//threshold(out, out, 128, 255, THRESH_BINARY_INV);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


	// 定义一个视频处理类处理视频帧
	// 首先创建实例
	VideoProcessor processor;
	// 打开视频文件
	processor.setInput("C:\\Users\\DELL\\Desktop\\504749319.flv");
	// 声明显示窗口
	// 分别为输入和输出视频
	processor.displayInput("Input Video");
	processor.displayOutput("Output Video");
	// 以原始帧率播放视频
	processor.setDelay(1000. / processor.getFrameRate());
	// 设置处理回调函数
	processor.setFrameProcessor(detect);
	// 开始帧处理过程
	processor.run();
	waitKey();
    return a.exec();
}
