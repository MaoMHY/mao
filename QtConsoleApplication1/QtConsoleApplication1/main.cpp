#include <QtCore/QCoreApplication>
#include "VideoProcessor.h"
#include <opencv2\opencv.hpp>
//#include "stdafx.h"

using namespace cv;
using namespace std;


void detect(Mat& img, Mat& out)
{
	//namedWindow("Camera");
	// ��Ҫ��ÿ֡ͼ��ת��Ϊ�Ҷ�ͼ
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
	// �����ؽ��з�ת
	//threshold(out, out, 128, 255, THRESH_BINARY_INV);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


	// ����һ����Ƶ�����ദ����Ƶ֡
	// ���ȴ���ʵ��
	VideoProcessor processor;
	// ����Ƶ�ļ�
	processor.setInput("C:\\Users\\DELL\\Desktop\\504749319.flv");
	// ������ʾ����
	// �ֱ�Ϊ����������Ƶ
	processor.displayInput("Input Video");
	processor.displayOutput("Output Video");
	// ��ԭʼ֡�ʲ�����Ƶ
	processor.setDelay(1000. / processor.getFrameRate());
	// ���ô���ص�����
	processor.setFrameProcessor(detect);
	// ��ʼ֡�������
	processor.run();
	waitKey();
    return a.exec();
}
