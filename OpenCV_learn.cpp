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
std::vector<int> paramsImage = std::vector<int>();

void foreachTest(Pixel &pixel)
{
	// cout << static_cast<int>(pixel.x) << "," << static_cast<int>(pixel.y) << "," << static_cast<int>(pixel.z) << endl;
	pixel.x = pixel.x * 10; //* 10;
	pixel.y = pixel.y * 10; //* 10;
	pixel.z = pixel.z * 10; //* 10;
}

void compressImage()
{
	Mat B = imread("./assets/a.png");
	imwrite("./assets/src.webp", B, paramsImage);

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
	// imwrite("./assets/test_compress.webp", C, paramsImage);
	imwrite("./assets/test_compress.jpg", C, paramsImage);
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
	// https://github.com/guofei9987/blind_watermark
	// 这个忙水印，a.png 可以看出图片不正常
	// https://github.com/guofei9987/blind_watermark/issues/57
	imshow("C 2", C);
	waitKey(0);
}
/**
 * 这里就可以解决一般的盲水印了。
 */
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
	imwrite("./assets/test_uncompress.jpg", B);
	waitKey(0);
}
/**
 * 解决这个
 * https://github.com/guofei9987/blind_watermark
 */
void uncompressImageWaterMaker()
{
	Mat B = imread("./assets/test_compress.png");
	// imshow("Equalized Image", B*5);
	// 不要乘以10 就ok， 越接近10 ， 提取出水印的概率越大。和 v[0] = v[0] * 10; 对应
	// 这个和 blind_watermark 的算法有关系，这一通操作就是把算法插入的数据破坏掉
	//
	imwrite("./assets/test_uncompress_remove_marker12.png", B * 9);
	waitKey(0);
	for (int r = 0; r < B.rows; r++)
	{
		// Loop over all columns
		for (int c = 0; c < B.cols; c++)
		{
			// Obtain pixel at (r, c)
			Vec3b &v = B.at<Vec3b>(r, c);
			v[0] = pow(v[0] / 255.0, 0.8) * 255.0 * 0.2;
			v[1] = pow(v[1] / 255.0, 0.8) * 255.0 * 0.2;
			v[2] = pow(v[2] / 255.0, 0.8) * 255.0 * 0.2;
		}
	}
	// 这个没测出什么情况下，可以解水印
	imwrite("./assets/test_uncompress_remove_marker.png", B * 15);
	imshow("Equalized Image", B * 15);
	waitKey(0);
}
// 阻止ai 识别(太费眼了)
void supperMark()
{
	Mat B = imread("./assets/a.png");

	// U 无符号整数, S  integer type   c
	Mat C(B.rows, B.cols, CV_8UC3);
	int m = 10;
	for (int r = 0; r < B.rows; r++)
	{
		// Loop over all columns
		for (int c = 0; c < B.cols; c++)
		{

			// if ((c) % m == 0 || (r) % m == 9)
			if ((c + r) % m <=1)
			{
				// 阻止AI 识别和线条(方块)的颜色(噪点)有很大的关系
				Vec3b &v = B.at<Vec3b>(r, c);
				// 注释下边任意一个，都能让blind_watermark失效
				v[0] = pow(v[0] / 255.0, 0.8) * 255.0 * 0.2;
				v[1] = pow(v[1] / 255.0, 0.8) * 255.0 * 0.2;
				v[2] = pow(v[2] / 255.0, 0.8) * 255.0 * 0.2;
			}
		}
	}
	imwrite("./assets/embedded.png", B);
	waitKey(0);
}
int main(int argc, char **argv)
{
	paramsImage.push_back(IMWRITE_WEBP_QUALITY);
	// >100 no loos
	paramsImage.push_back(80);
	// compressImage();
	// uncompressImage();
	// uncompressImageWaterMaker();
	supperMark();
	return 0;
}
