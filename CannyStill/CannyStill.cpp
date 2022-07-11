//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/highgui.hpp"
//#include "opencv2/imgproc.hpp"
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include<iostream>
#include<conio.h>           // may have to modify this line if not using Window

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

namespace
{
	// windows and trackbars name
	const std::string windowName = "Hough Circle Detection Demo";
	const std::string cannyThresholdTrackbarName = "Canny threshold";
	const std::string accumulatorThresholdTrackbarName = "Accumulator Threshold";
	const std::string usage = "Usage : tutorial_HoughCircle_Demo <path_to_input_image>\n";

	// initial and max values of the parameters of interests.
	const int cannyThresholdInitialValue = 200;
	const int accumulatorThresholdInitialValue = 50;
	const int maxAccumulatorThreshold = 200;
	const int maxCannyThreshold = 255;

	void HoughDetection(const Mat& src_gray, const Mat& src_display, int cannyThreshold, int accumulatorThreshold)
	{
		// will hold the results of the detection
		std::vector<Vec3f> circles;
		// runs the actual detection
		HoughCircles(src_gray, circles, HOUGH_GRADIENT, 1, src_gray.rows / 8, cannyThreshold, accumulatorThreshold, 0, 0);

		// clone the colour, input image for displaying purposes
		Mat display = src_display.clone();
		for (size_t i = 0; i < circles.size(); i++)
		{
			Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
			int radius = cvRound(circles[i][2]);
			// circle center
			circle(display, center, 3, Scalar(0, 255, 0), -1, 8, 0);
			// circle outline
			circle(display, center, radius, Scalar(0, 0, 255), 3, 8, 0);
		}

		// shows the results
		imshow(windowName, display);
	}
}


int main()
{
	Mat src, src_gray;

	
	string imageSource = "C:\\image.jpg";
	// Read the image
	src = imread(imageSource, IMREAD_COLOR);

	if (src.empty())
	{
		std::cerr << "Invalid input image\n";
		std::cout << usage;
		return -1;
	}

	// Convert it to gray
	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	// Reduce the noise so we avoid false circle detection
	GaussianBlur(src_gray, src_gray, Size(9, 9), 2, 2);

	//declare and initialize both parameters that are subjects to change
	int cannyThreshold = cannyThresholdInitialValue;
	int accumulatorThreshold = accumulatorThresholdInitialValue;

	// create the main window, and attach the trackbars
	namedWindow(windowName, WINDOW_AUTOSIZE);
	createTrackbar(cannyThresholdTrackbarName, windowName, &cannyThreshold, maxCannyThreshold);
	createTrackbar(accumulatorThresholdTrackbarName, windowName, &accumulatorThreshold, maxAccumulatorThreshold);

	// infinite loop to display
	// and refresh the content of the output image
	// until the user presses q or Q
	char key = 0;
	while (key != 'q' && key != 'Q')
	{
		// those paramaters cannot be =0
		// so we must check here
		cannyThreshold = std::max(cannyThreshold, 1);
		accumulatorThreshold = std::max(accumulatorThreshold, 1);

		//runs the detection, and update the display
		HoughDetection(src_gray, src, cannyThreshold, accumulatorThreshold);

		// get user key
		key = (char)waitKey(10);
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//int main() {
//
//	cv::Mat imgOriginal;        // input image
//	cv::Mat imgGrayscale;       // grayscale of input image
//	cv::Mat imgBlurred;         // intermediate blured image
//	cv::Mat imgCanny;           // Canny edge image
//
//	imgOriginal = cv::imread("image.jpg");          // open image
//
//
//

//static void help()
//{
//	cout << "\nThis program demonstrates circle finding with the Hough transform.\n"
//		"Usage:\n"
//		"./houghcircles <image_name>, Default is image.jpg\n" << endl;
//}
//
//int main(int argc, char** argv)
//{
//
//	/*cv::CommandLineParser parser(argc, argv,
//		"{help h ||}{@image|../data/board.jpg|}"*/
//	cv::CommandLineParser parser(argc, argv,
//		"{help h ||}{@image|/12circles.png|}"
//	);
//	if (parser.has("help"))
//	{
//		help();
//		return 0;
//	}
//	//![load]
//    string filename = parser.get<string>("@image");  //parser.get<string>("@image");
//	Mat img = imread(filename, IMREAD_COLOR);
//	if (img.empty())
//	{
//		help();
//		cout << "can not open " << filename << endl;
//		return -1;
//	}
//	//![load]
//
//	//![convert_to_gray]
//	Mat gray;
//	cvtColor(img, gray, COLOR_BGR2GRAY);
//	//![convert_to_gray]
//
//	//![reduce_noise]
//	medianBlur(gray, gray, 5);
//	//![reduce_noise]
//
//	//![houghcircles]
//	vector<Vec3f> circles;
//	HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
//		gray.rows / 16, // change this value to detect circles with different distances to each other
//		100, 30, 1, 30 // change the last two parameters
//					   // (min_radius & max_radius) to detect larger circles
//	);
//	//![houghcircles]
//
//	//![draw]
//	for (size_t i = 0; i < circles.size(); i++)
//	{
//		Vec3i c = circles[i];
//		circle(img, Point(c[0], c[1]), c[2], Scalar(0, 0, 255), 3, LINE_AA);
//		circle(img, Point(c[0], c[1]), 2, Scalar(0, 255, 0), 3, LINE_AA);
//	}
//	//![draw]
//
//	//![display]
//	imshow("detected circles", img);
//	waitKey();
//	//![display]
//
//	return 0;
//}






// CannyStill.cpp

//#include<opencv2/core/core.hpp>
//#include<opencv2/highgui/highgui.hpp>
//#include<opencv2/imgproc/imgproc.hpp>
//
//#include<iostream>
//#include<conio.h>           // may have to modify this line if not using Windows
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//int main() {
//
//	cv::Mat imgOriginal;        // input image
//	cv::Mat imgGrayscale;       // grayscale of input image
//	cv::Mat imgBlurred;         // intermediate blured image
//	cv::Mat imgCanny;           // Canny edge image
//
//	imgOriginal = cv::imread("image.jpg");          // open image
//
//	if (imgOriginal.empty()) {                                  // if unable to open image
//		std::cout << "error: image not read from file\n\n";     // show error message on command line
//		_getch();                                               // may have to modify this line if not using Windows
//		return(0);                                              // and exit program
//	}
//
//	cv::cvtColor(imgOriginal, imgGrayscale, CV_BGR2GRAY);       // convert to grayscale
//
//	cv::GaussianBlur(imgGrayscale,          // input image
//		imgBlurred,                         // output image
//		cv::Size(5, 5),                     // smoothing window width and height in pixels
//		1.5);                               // sigma value, determines how much the image will be blurred
//
//	cv::Canny(imgBlurred,           // input image
//		imgCanny,                   // output image
//		100,                        // low threshold
//		200);                       // high threshold
//
//									// declare windows
//	cv::namedWindow("imgOriginal", CV_WINDOW_AUTOSIZE);     // note: you can use CV_WINDOW_NORMAL which allows resizing the window
//	cv::namedWindow("imgCanny", CV_WINDOW_AUTOSIZE);        // or CV_WINDOW_AUTOSIZE for a fixed size window matching the resolution of the image
//															// CV_WINDOW_AUTOSIZE is the default
//	cv::imshow("imgOriginal", imgOriginal);     // show windows
//	cv::imshow("imgCanny", imgCanny);
//
//	cv::waitKey(0);                 // hold windows open until user presses a key
//
//	return(0);
//}

// RedBallTracker.cpp

//#include<opencv2/core/core.hpp>
//#include<opencv2/highgui/highgui.hpp>
//#include<opencv2/imgproc/imgproc.hpp>
//
//#include<iostream>
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//int main() {
//	cv::VideoCapture capWebcam(0);		// declare a VideoCapture object and associate to webcam, 0 => use 1st webcam
//
//	if (capWebcam.isOpened() == false) {				// check if VideoCapture object was associated to webcam successfully
//		std::cout << "error: capWebcam not accessed successfully\n\n";	// if not, print error message to std out
//		return(0);														// and exit program
//	}
//
//	cv::Mat imgOriginal;		// input image
//	cv::Mat imgHSV;
//	cv::Mat imgThreshLow;
//	cv::Mat imgThreshHigh;
//	cv::Mat imgThresh;
//
//	std::vector<cv::Vec3f> v3fCircles;				// 3 element vector of floats, this will be the pass by reference output of HoughCircles()
//
//	char charCheckForEscKey = 0;
//
//	while (charCheckForEscKey != 27 && capWebcam.isOpened()) {		// until the Esc key is pressed or webcam connection is lost
//		bool blnFrameReadSuccessfully = capWebcam.read(imgOriginal);		// get next frame
//
//		if (!blnFrameReadSuccessfully || imgOriginal.empty()) {		// if frame not read successfully
//			std::cout << "error: frame not read from webcam\n";		// print error message to std out
//			break;													// and jump out of while loop
//		}
//
//		cv::cvtColor(imgOriginal, imgHSV, CV_BGR2HSV);
//
//		cv::inRange(imgHSV, cv::Scalar(0, 155, 155), cv::Scalar(18, 255, 255), imgThreshLow);
//		cv::inRange(imgHSV, cv::Scalar(165, 155, 155), cv::Scalar(179, 255, 255), imgThreshHigh);
//
//		cv::add(imgThreshLow, imgThreshHigh, imgThresh);
//
//		cv::GaussianBlur(imgThresh, imgThresh, cv::Size(3, 3), 0);
//
//		cv::Mat structuringElement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
//
//		cv::dilate(imgThresh, imgThresh, structuringElement);
//		cv::erode(imgThresh, imgThresh, structuringElement);
//
//		// fill circles vector with all circles in processed image
//		cv::HoughCircles(imgThresh,			// input image
//			v3fCircles,							// function output (must be a standard template library vector
//			CV_HOUGH_GRADIENT,					// two-pass algorithm for detecting circles, this is the only choice available
//			2,									// size of image / this value = "accumulator resolution", i.e. accum res = size of image / 2
//			imgThresh.rows / 4,				// min distance in pixels between the centers of the detected circles
//			100,								// high threshold of Canny edge detector (called by cvHoughCircles)						
//			50,									// low threshold of Canny edge detector (set at 1/2 previous value)
//			10,									// min circle radius (any circles with smaller radius will not be returned)
//			400);								// max circle radius (any circles with larger radius will not be returned)
//
//		for (int i = 0; i < v3fCircles.size(); i++) {		// for each circle . . .
//															// show ball position x, y, and radius to command line
//			std::cout << "ball position x = " << v3fCircles[i][0]			// x position of center point of circle
//				<< ", y = " << v3fCircles[i][1]								// y position of center point of circle
//				<< ", radius = " << v3fCircles[i][2] << "\n";				// radius of circle
//
//																			// draw small green circle at center of detected object
//			cv::circle(imgOriginal,												// draw on original image
//				cv::Point((int)v3fCircles[i][0], (int)v3fCircles[i][1]),		// center point of circle
//				3,																// radius of circle in pixels
//				cv::Scalar(0, 255, 0),											// draw pure green (remember, its BGR, not RGB)
//				CV_FILLED);														// thickness, fill in the circle
//
//																				// draw red circle around the detected object
//			cv::circle(imgOriginal,												// draw on original image
//				cv::Point((int)v3fCircles[i][0], (int)v3fCircles[i][1]),		// center point of circle
//				(int)v3fCircles[i][2],											// radius of circle in pixels
//				cv::Scalar(0, 0, 255),											// draw pure red (remember, its BGR, not RGB)
//				3);																// thickness of circle in pixels
//		}	// end for
//
//			// declare windows
//		cv::namedWindow("imgOriginal", CV_WINDOW_AUTOSIZE);	// note: you can use CV_WINDOW_NORMAL which allows resizing the window
//		cv::namedWindow("imgThresh", CV_WINDOW_AUTOSIZE);	// or CV_WINDOW_AUTOSIZE for a fixed size window matching the resolution of the image
//															// CV_WINDOW_AUTOSIZE is the default
//
//		cv::imshow("imgOriginal", imgOriginal);			// show windows
//		cv::imshow("imgThresh", imgThresh);
//
//		charCheckForEscKey = cv::waitKey(1);			// delay (in ms) and get key press, if any
//	}	// end while
//
//	return(0);
//}