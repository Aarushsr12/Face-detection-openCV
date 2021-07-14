#include<opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>
#include<iostream>

using namespace std;
using namespace cv;

//HaarCascades Approach
void face_Detect(Mat img, CascadeClassifier faceCascade)
{

	faceCascade.load("haarcascade_frontalface_default.xml");
	if (faceCascade.empty()) {
		cout << "XML file not loaded" << endl;
	}
	vector<Rect> faces;
	faceCascade.detectMultiScale(img, faces, 1.1, 10);

	int count = 0;
	for (int i = 0; i < faces.size(); ++i) {
		rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);
		count += 1;
	}
	string temp = to_string(count);

	putText(img,"No of faces:  "+temp, Point(25, 30), FONT_HERSHEY_COMPLEX_SMALL, 1, LINE_AA);
	imshow("Picture_Detection", img);
	waitKey(0);
}

void motion_detect(Mat img1, CascadeClassifier motionCascade)
{
	VideoCapture cap(0);
	motionCascade.load("haarcascade_frontalface_default.xml");
	if (motionCascade.empty()) {
		cout << "XML file not loaded"<<endl;
	}
	vector<Rect> faces1;

	while (true)
	{
		cap.read(img1);
		motionCascade.detectMultiScale(img1, faces1, 1.1, 8);
		int count1 = 0;
		for (int i = 0; i < faces1.size(); ++i) {
			rectangle(img1, faces1[i].tl(), faces1[i].br(), Scalar(0, 255,0), 3);
			count1 += 1;
		}
		string temp1 = to_string(count1);
		putText(img1, "No of faces:  " + temp1, Point(30, 45), FONT_HERSHEY_COMPLEX_SMALL, 1, LINE_AA);
		imshow("Motion_Detection", img1);
		waitKey(1);
	}
}

int main()
{
	string path;
	Mat img1, img2;
	CascadeClassifier faceCascade, motionCascade;
	cout << "*************************************************************************\n";

	cout << "\tWelcome to Real-Time Face Recognition System !!" << endl;

	cout << "\n 1.Multiple Face-Recognition\n 2.Live Face-Recongition(Inbuilt-Camera)\n";
start:
	cout << "\nSelect an option to continue.....\n";
	int option;
	cin >> option;
	switch (option)
	{
	case 1: cout << "Enter File name & extension(.jpg/.png)\n";
			cin >> path;
			img1 = imread(path);
			face_Detect(img1, faceCascade);
			break;

	case 2: cout << "Opening Camera....." << endl;
			motion_detect(img2, motionCascade);
			break;

	default: cout << "Invalid Input" << "\n";
			goto start;
	}
	return 0;
}