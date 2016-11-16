#include <iostream>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\opencv.hpp>
#include <cstdlib>
#include <ctime>
#include <vector>
#define AMPLIFY 1
#define WORKING_RATE 100
#define LAYOUT 1

using namespace cv;
using namespace std;
int main() {
	srand(time(0));
	Mat rawImg = imread("rawImage.png", 0);
	Mat sumImg = imread("rawImage.png", 0);
	if (rawImg.empty())
		cerr << "whaa raw img cannot be loaded!" << endl;

	const int WIDTH = rawImg.rows;
	const int HEIGHT = rawImg.cols;
	unsigned char sum = 0;

	namedWindow("Picture_1", CV_WINDOW_FREERATIO);
	imshow("Picture_1", rawImg);

	int direction[][2] = { {0,1}, {0,-1}, {1,0}, {-1,0}, {-1,-1}, {-1, 1}, {1, 1}, {1, -1} };

	for (int a = 0; a < AMPLIFY; ++a) {
		for (int i = 1; i < WIDTH - 1; ++i)
			for (int j = 1; j < HEIGHT - 1; ++j) {
				sum = 0;
				for (int n = 0; n < 4* LAYOUT; ++n)
					if (rand() % 100 < WORKING_RATE)
						sum += rawImg.at<uchar>(i + direction[n][0], j + direction[n][1]);
				sum /= 4;
				sumImg.at<uchar>(i, j) = sum;
			}
		for (int i = 1; i < WIDTH; ++i)
			for (int j = 1; j < HEIGHT - 1; ++j)
				rawImg.at<uchar>(i, j) -= sumImg.at<uchar>(i,j);
	}

#if 0
	Scalar intensity = rawImg.at<uchar>(0, 1);
#endif

	namedWindow("Picture_2", CV_WINDOW_FREERATIO);
	imshow("Picture_2", rawImg);
	waitKey(0);
}