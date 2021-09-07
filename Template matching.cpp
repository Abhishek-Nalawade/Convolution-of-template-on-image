#include<opencv2\opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main() {
	int i, height, width, count = 0, percent, progress, r, c, x, y, g = 0, h = 0, k = 0;
	cout << "Enter the height of the image :"<<endl;
	cin >> height;
	cout <<endl<< "Enter the width of the image :" << endl;
	cin >> width;
	Mat img = imread("circles.png");
	Mat tmp = imread("template.jpg");
	int arr1[224][225][3]; //main image
	int arr2[59][59][3]; //template
	for ( r = 0; r < img.rows; r++) {
		for ( c = 0; c < img.cols; c++) {
			int a, b, d, *p, *q, *s;
			a = img.at<Vec3b>(r, c)(0);
			b = img.at<Vec3b>(r, c)(1);
			d = img.at<Vec3b>(r, c)(2);
			p = &a;
			q = &b;
			s = &d;
			int arr[3] = { *p,*q,*s };
			for (i = 0; i < 3; i++) {
				arr1[r][c][i] = arr[i];
			}
			
		}
	}
	

	//matrix formation for template image
	
	for ( r = 0; r < tmp.rows; r++) {
		for ( c = 0; c < tmp.cols; c++) {
			int a, b, d, *p, *q, *s;
			a = tmp.at<Vec3b>(r, c)(0);
			b = tmp.at<Vec3b>(r, c)(1);
			d = tmp.at<Vec3b>(r, c)(2);
			p = &a;
			q = &b;
			s = &d;
			int arr[3] = { *p,*q,*s };
			for (i = 0; i < 3; i++) {
				arr2[r][c][i] = arr[i];
			}
		
		}
	}
	

	//comparing the values of img and tmp
	for (int m = 0; m < (img.rows - tmp.rows); m++) {
		for (int n = 0; n < (img.cols-tmp.cols); n++) {
			for ( r = 0; r < tmp.rows; r++) {
				for ( c = 0; c < tmp.cols; c++) {
					for (i = 0; i < 3; i++) {
						int a, b;
						a = arr1[m + r][n + c][i] - 25;      //deflection of 50
						b = arr1[m + r][n + c][i] + 25;
						if (a <= arr2[r][c][i] && arr2[r][c][i] <= b )count++;
						else;
						
						
					}
				}
				//reducing number of iterations
				//currently increases by 16%
				percent = (count * 100) / 10443;
				progress = (r * 100) / tmp.rows;
				if (progress >= 60 && percent <= 50) {
					k++;
					break;
				}
				else;
			}
			percent = (count * 100) / 10443;
			if (percent > 85) {
				cout << m + r - 59 << endl << n + c - 59 <<endl<<  percent << endl << endl;
				//mark at the start image
				//img.at<Vec3b>(m + r - 59, n + c - 59)(0) = 0;
				//img.at<Vec3b>(m + r - 59, n + c - 59)(1) = 0;
				//img.at<Vec3b>(m + r - 59, n + c - 59)(2) = 150;
				
				//marks at end of coloumns
					for (int h = 0; h < 59; h++) {
						int q = 0;
						for (int i = 0; i < 2; i++) {
							img.at<Vec3b>(m + q, n + h)(0) = 0;
							img.at<Vec3b>(m + q, n + h)(1) = 200;
							img.at<Vec3b>(m + q, n + h)(2) = 0;
							q = 58;
						}
					}

				//marks at end of rows
					for (int g = 1; g < 58; g++) {
						int q = 0;
						for (int i = 0; i < 2; i++) {
							img.at<Vec3b>(m + g, n + q)(0) = 0;
							img.at<Vec3b>(m + g, n + q)(1) = 200;
							img.at<Vec3b>(m + g, n + q)(2) = 0;
							q = 58;
						}
					}
					
				
				//mark at end of image
				//img.at<Vec3b>(m + r , n + c )(0) = 0;
				//img.at<Vec3b>(m + r , n + c )(1) = 0;
				//img.at<Vec3b>(m + r , n + c )(2) = 150;
			}
			else;
			 
			count = 0;
		}
	}
	cout << endl << k << endl;
	namedWindow("result", WINDOW_NORMAL);
	imshow("result", img);
	waitKey();

}