// money-test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <math.h>
#include "cv.h"
#include <string>
#include <iostream>  
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"  
#pragma comment(lib,"opencv_highgui2410d.lib")

using namespace cv;  
using namespace std;  

int main( int argc, char** argv )  
{  

	char c;
	CvCapture* capture = cvCreateCameraCapture(0);   //0Ϊ�ⲿ����ͷ��ID��1Ϊ�ʼǱ���������ͷ��ID 2016��4��10�� 12:31:59������
	IplImage* src;
	for (;;) 
	{
		src = cvQueryFrame(capture);            
		cvShowImage("Input", src);
		c = waitKey(10);
		if (c == 27) break;
	} 
	return 0;


















	//IplImage *image,*hsv,*H_hue,*S_saturation,*V_value;//ͼ��ռ�
	//image=cvLoadImage("lena.bmp");//��ͼ��Դͼ��

	//hsv=cvCreateImage(cvGetSize(image),8,3);//��hsvɫϵ��ͼ������ռ�
	//H_hue=cvCreateImage(cvGetSize(image),8,1);  //ɫ��
	//S_saturation=cvCreateImage(cvGetSize(image),8,1);//���Ͷ�
	//V_value=cvCreateImage(cvGetSize(image),8,1);//����

	////cvNamedWindow("image",CV_WINDOW_AUTOSIZE);//������ʾͼ��Ĵ���
	////cvNamedWindow("hsv",CV_WINDOW_AUTOSIZE);
	////cvNamedWindow("H_hue",CV_WINDOW_AUTOSIZE);
	////cvNamedWindow("S_saturation",CV_WINDOW_AUTOSIZE);
	////cvNamedWindow("V_value",CV_WINDOW_AUTOSIZE);

	//cvCvtColor(image,hsv,CV_BGR2HSV);//��RGBɫϵתΪHSVɫϵ

	////cvShowImage("image",image);
	////cvShowImage("hsv",hsv);

	//cvSplit(hsv, H_hue, 0, 0, 0 );//��������ͨ��
	//cvSplit(hsv, 0, S_saturation, 0, 0 );
	//cvSplit(hsv, 0, 0, V_value, 0 );

	//CvScalar value_H = cvGet2D(H_hue,0,0);
	//printf("%f  %f  %f",value_H.val[0],value_H.val[1],value_H.val[2]);

	//cvShowImage("H_hue",H_hue);
	//cvShowImage("S_saturation",S_saturation);
	//cvShowImage("V_value",V_value);
	//cvWaitKey(0);
	//cvDestroyWindow("image");
	//cvDestroyWindow("hsv");
	//cvDestroyWindow("H_hue");
	//cvDestroyWindow("S_saturation");
	//cvDestroyWindow("V_value");
	//return 0;







	//IplImage* image = cvLoadImage("lena.bmp");  
	//IplImage* hsv = cvCreateImage( cvGetSize(image), 8, 3 );
	//cvCvtColor(image,hsv,CV_BGR2HSV);

	//cvNamedWindow("saturate_SV",CV_WINDOW_AUTOSIZE);  
	//cvShowImage("saturate_SV",hsv);  
	//cvWaitKey(0);  
	//cvReleaseImage(&hsv);  
	//cvDestroyWindow("saturate_SV");  
	//return 0;

	//string imageName = "lena.bmp";
	//Mat img = imread(imageName,CV_LOAD_IMAGE_COLOR);
	//if (img.empty())
	//{
	//	cout<<"could not open or find the image !"<<endl;
	//}
	//cout<<img<<endl;

	//namedWindow("lena",CV_WINDOW_AUTOSIZE);
	//imshow("lena",img);
	//waitKey();

	//return 0;  

}  