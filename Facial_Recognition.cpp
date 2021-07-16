#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//HaarCascades Approach
void face_Detect(Mat img, CascadeClassifier faceCascade) //function for face detection in image
{
	faceCascade.load("haarcascade_frontalface_default.xml"); //loading xml file for detecting frontal faces
	if (faceCascade.empty()) // if file detected as empty
	{
		cout << "XML file not loaded" << endl;
	}
	vector<Rect> faces;	//creating a vector 'rect' that is an instance of SVG shape and draws rectangles at defined positions
	faceCascade.detectMultiScale(img, faces, 1.1, 10); //function detecting objects of different sizes in the input image and returing vector of rectangles

	int face_count = 0; //initaizing the face count to 0
	for (int i = 0; i < faces.size(); ++i)
	{
		rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3); //making rectangles on detected faces
		face_count += 1; //incrementing face_count by 1 each time a face is found
	}
	string temp = to_string(face_count); //storing count of faces as string in temporary variable

	putText(img, "No of faces:  " + temp, Point(25, 30), FONT_HERSHEY_COMPLEX_SMALL, 1, LINE_AA); //printing text at top right corner showing number of faces
	imshow("Picture_Detection", img); //detecting faces in a new window named	'Picture_Detection'
	waitKey(0);	//displaying Picture_Detection window infinitely until any keypress
}

void motion_detect(Mat img1, CascadeClassifier motionCascade) //function for face detection in video
{
	VideoCapture cap(0); //function for capturing video
	motionCascade.load("haarcascade_frontalface_default.xml"); //loading xml file for motion detection in video
	if (motionCascade.empty()) //if file found empty
	{
		cout << "XML file not loaded" << endl;
	}
	vector<Rect> faces1; //vector of rect

	while (true) //infinite loop
	{
		cap.read(img1);	//reading frame of detected video
		motionCascade.detectMultiScale(img1, faces1, 1.1, 8); //detecting objects of different sizes
		int face_count2 = 0; //face count in video initialized as 0
		for (int i = 0; i < faces1.size(); ++i)
		{
			rectangle(img1, faces1[i].tl(), faces1[i].br(), Scalar(0, 255, 0), 3); //making rectangles on faces
			face_count2 += 1; //incrementing face count by 1
		}
		string temp1 = to_string(face_count2);	//coverting face_count2 to string
		putText(img1, "No of faces:  " + temp1, Point(30, 45), FONT_HERSHEY_COMPLEX_SMALL, 1, LINE_AA); //printing text at top left corner with face count
		imshow("Motion_Detection", img1);	//new window for video
		waitKey(1);	//displaying window infinitely
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
	case 1:
		cout << "Enter File name & extension(.jpg/.png)\n";
		cin >> path;
		img1 = imread(path);
		face_Detect(img1, faceCascade);
		break;

	case 2:
		cout << "Opening Camera....." << endl;
		motion_detect(img2, motionCascade);
		break;

	default:
		cout << "Invalid Input\n";
		goto start;
	}
	return 0;
}