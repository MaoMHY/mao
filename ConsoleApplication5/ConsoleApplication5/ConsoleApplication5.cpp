// ConsoleApplication5.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <opencv2\opencv.hpp>
#include <opencv2\video\tracking.hpp>
#include "stdafx.h"
#include <iostream>
#include <opencv.hpp>
#include <opencv2\imgproc\types_c.h>
using namespace std;
using namespace cv;

#define SSTR( x ) static_cast< std::ostringstream & >( ( std::ostringstream() << std::dec << x ) ).str()

int main()
{

	string trackerTypes[6] = { "BOOSTING", "MIL", "KCF", "TLD","MEDIANFLOW", "GOTURN" };
	// vector <string> trackerTypes(types, std::end(types));

	// ����tracker
	string trackerType = trackerTypes[2];

	Ptr<Tracker> tracker;

	tracker = TrackerMIL::create();

	//#if (CV_MINOR_VERSION < 3)
	//	{
	//		tracker = Tracker::create(trackerType);
	//	}
	//#else
	//	{
	//		if (trackerType == "BOOSTING")
	//			tracker = TrackerBoosting::create();
	//		if (trackerType == "MIL")
	//			tracker = TrackerMIL::create();
	//		if (trackerType == "KCF")
	//			tracker = TrackerKCF::create();
	//		if (trackerType == "TLD")
	//			tracker = TrackerTLD::create();
	//		if (trackerType == "MEDIANFLOW")
	//			tracker = TrackerMedianFlow::create();
	//		if (trackerType == "GOTURN")
	//			tracker = TrackerGOTURN::create();
	//	}
	//#endif
	
	// ��ȡ��Ƶ
	VideoCapture video("C:\\Users\\DELL\\Desktop\\504749319.flv");

	if (!video.isOpened())
	{
		cout << "Could not read video file" << endl;
		return 1;

	}

	// ��ȡ��һ֡
	Mat frame;
	bool ok = video.read(frame);

	// ��������ĸ��ٿ�
	Rect bbox;
	Mat tframe;
	// ͨ���������ģ�ͼ�����һ������
	while (video.read(frame)) {
		// ��Ҫ��ÿ֡ͼ��ת��Ϊ�Ҷ�ͼ
		cvtColor(frame, tframe, CV_BGR2GRAY);
		equalizeHist(tframe, tframe);
		CascadeClassifier faces_cascade;
		faces_cascade.load("F:\\opencv455\\opencv\\sources\\data\\haarcascades_cuda\\haarcascade_frontalface_alt.xml");
		vector<Rect> faces;
		faces_cascade.detectMultiScale(tframe, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
		if (faces.size() != 0) {
			Rect roi = faces[0];
			bbox.x = roi.x;
			bbox.y = roi.y;
			bbox.width = roi.width;
			bbox.height = roi.height;
			break;
		}
	}

	// Uncomment the line below to select a different bounding box
	//bbox = selectROI(frame, false);

	// �������ٿ�
	rectangle(frame, bbox, Scalar(255, 0, 0), 2, 1);
	imshow("Tracking", frame);

	tracker->init(frame, bbox);

	while (video.read(frame))
	{
		// ��ʼʱ��
		double timer = (double)getTickCount();

		// ���¸��ٽ��
		bool ok = tracker->update(frame, bbox);

		// ����fps
		float fps = getTickFrequency() / ((double)getTickCount() - timer);

		if (ok)
		{
			// ���ٳɹ����������ٿ�
			rectangle(frame, bbox, Scalar(255, 0, 0), 2, 1);
		}
		else
		{
			// ����ʧ��
			putText(frame, "Tracking failure detected", Point(100, 80), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 255), 2);
		}

		// Display tracker type on frame
		putText(frame, trackerType + " Tracker", Point(100, 20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50, 170, 50), 2);

		// Display FPS on frame
		putText(frame, "FPS : " + SSTR(int(fps)), Point(100, 50), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50, 170, 50), 2);

		// Display frame.
		imshow("Tracking", frame);

		// Exit if ESC pressed.
		int k = waitKey(1);
		if (k == 'q')
		{
			break;
		}

	}
    return 0;
}

