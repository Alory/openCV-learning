// openCVTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

static void contrastAndBright(int, void*);

int contrastValue;
int brightValue;
Mat srcImage, dstImage;

int main(int argc, char** argv)
{
	system("color 5E");
	
	srcImage = imread("girl.jpg");
	if(!srcImage.data){cout<<"Where is the girl?"<<endl; return false;}
	dstImage = Mat::ones(srcImage.size(),srcImage.type());

	contrastValue = 60;
	brightValue = 60;
	namedWindow("final graph",1);

	createTrackbar("对比度","final graph",&contrastValue,300,contrastAndBright);
	createTrackbar("亮度","final graph",&brightValue,300,contrastAndBright);

	cout<<endl<<"按下“q”键退出\n";

	while(char(waitKey(1)) != 'q' ){}
	return  0;
}

static void contrastAndBright(int ,void*){
	namedWindow("original graph",1);

	for(int i=0;i<srcImage.rows;i++){
		for(int j=0;j<srcImage.cols;j++){
			for(int k=0;k<3;k++){
				dstImage.at<Vec3b>(i,j)[k] = saturate_cast<uchar>((contrastValue*0.01)*srcImage.at<Vec3b>(i,j)[k]+brightValue);
			}
		}
	}

	imshow("original graph",srcImage);
	imshow("final graph",dstImage);
}