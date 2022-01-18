#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

typedef Point3_<uint8_t> Pixel;

typedef Point3_<uint8_t> Pixel5;

void foreachTest(Pixel &pixel)
{
	// cout << static_cast<int>(pixel.x) << "," << static_cast<int>(pixel.y) << "," << static_cast<int>(pixel.z) << endl;
	pixel.x = pixel.x * 10; //* 10;
	pixel.y = pixel.y * 10; //* 10;
	pixel.z = pixel.z * 10; //* 10;
}

void compressImage()
{
	Mat B = imread("./assets/b.jpg");
	// B.forEach<Pixel>(
	// 	[](Pixel &pixel, const int *position) -> void
	// 	{
	// 		complicatedThreshold(pixel);
	// 	});
	// Vec3b v = B.at<Vec3b>(0, 0);
	// cout << static_cast<int>(v[0]) << endl;
	// cout << static_cast<int>(v[1]) << endl;
	// cout << static_cast<int>(v[2]) << endl;
	// U 无符号整数, S  integer type   c
	Mat C(B.rows, B.cols, CV_8UC3);
	for (int r = 0; r < B.rows; r++)
	{
		// Loop over all columns
		for (int c = 0; c < B.cols; c++)
		{
			// Obtain pixel at (r, c)
			Vec3b &v = B.at<Vec3b>(r, c);
			Vec3b &vc = C.at<Vec3b>(r, c);
			vc[0] = (static_cast<int>(v[0] / 10));
			vc[1] = (static_cast<int>(v[1] / 10));
			vc[2] = (static_cast<int>(v[2] / 10));
			// cout << static_cast<int>(v[0]) << "," << static_cast<int>(v[1]) << "," << static_cast<int>(v[2]) << endl;
		}
	}
	imshow("B", B);
	imshow("C", C);
	imwrite("./assets/test_compress.jpg", C);
	waitKey(0);
	for (int r = 0; r < C.rows; r++)
	{
		for (int c = 0; c < B.cols; c++)
		{
			Vec3b &v = C.at<Vec3b>(r, c);
			v[0] = v[0] * 10;
			v[1] = v[1] * 10;
			v[2] = v[2] * 10;
		}
	}
	imshow("C 2", C);
	waitKey(0);
}
void uncompressImage()
{
	Mat B = imread("./assets/test_compress.jpg");
	for (int r = 0; r < B.rows; r++)
	{
		// Loop over all columns
		for (int c = 0; c < B.cols; c++)
		{
			// Obtain pixel at (r, c)
			Vec3b &v = B.at<Vec3b>(r, c);
			v[0] = v[0] * 10;
			v[1] = v[1] * 10;
			v[2] = v[2] * 10;
		}
	}
	imshow("uncompress", B);
	waitKey(0);
}
int main(int argc, char **argv)
{
	compressImage();
	uncompressImage();
	return 0;
}
