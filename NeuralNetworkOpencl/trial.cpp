#include<iostream>
#include<string>
#include <opencv2/opencv.hpp>
#include <cv.h>
#include <highgui.h>
#include "NeuralNet.h"

#define trainSamples 60000
#define testSamples 10000
#define OutputLength 10
#define ROW 28
#define COL 28
#define Layer_1_Size ROW*COL+1
#define Layer_2_Size 28


using namespace std;
using namespace cv;

float X[trainSamples][Layer_1_Size];
float Y[trainSamples][OutputLength];
float theta1[Layer_2_Size-1][Layer_1_Size];
float theta2[OutputLength][Layer_2_Size];

int fIndex[10];


typedef struct {
	int type=0;
	int count=0;
	vector<float*> stream;
} sample;


int save_img(int row,int column, float *bytes, int n, string folder){
	string filetype=".png";
	string folderloc="./";
	string filename=std::to_string(n);
	string ind=std::to_string(fIndex[n]);
	string address=folderloc+folder+'/'+filename+'/'+filename+"_"+ind+filetype;
	cout<<address<<endl;
	Mat image(row,column, CV_32FC1, bytes);
	imwrite( address, image);
//	namedWindow(filename);
//	imshow( filename, image);
//	waitKey(0);
	fIndex[n]++;

	return 0;
}
	

void convertToStream( float *strs[OutputLength], sample streams[OutputLength]) {
	for(int i=0;i<OutputLength;i++) {
		int length=streams[i].count;
		float *temp[length];
		for(int j=0;j<length;j++) {
			temp[j]=streams[i].stream.at(j);
		}
		strs[i]=(float *) temp;
	}
}

int main(){
	int n;
	int row=ROW;
	int column=COL;
	sample streams[OutputLength];
	int totPix=row*column;
	
/////////////////Preparing Training Set//////////////////////////////
	for(int k=0;k<trainSamples;k++){
		X[k][0]=1;
	}
	
	FILE *fp;
	fp=fopen("mnist_train.csv","r");
	for(int k=0;(k<trainSamples||(!feof(fp)));k++){
		fscanf(fp,"%d,",&n);
		float *bytes=(float *)calloc(totPix,sizeof(float));
		for(int i=0;i<totPix;i++){
			fscanf(fp,"%f,",&bytes[i]);
			X[k][i+1]=bytes[i];
			//cout<<bytes[i]<<",";
		}
		for(int i=0;i<OutputLength;i++){
			if(i==n){
				Y[k][i]=1;
			}
			else{
				Y[k][i]=0;
			}
		}
		
		
//		save_img(row,column, bytes, n, "train");
		streams[n].type=n;
		streams[n].count++;
		streams[n].stream.push_back(bytes);
		

	}
	fclose(fp);
	
/////////////////Preparing Testing Set//////////////////////////////

	for(int k=0;k<trainSamples;k++){
		X[k][0]=1;
	}
	fp=fopen("mnist_test.csv","r");
	for(int k=0;(k<testSamples||(!feof(fp)));k++){
		fscanf(fp,"%d,",&n);
		float *bytes=(float *)calloc(totPix,sizeof(float));
		for(int i=0;i<totPix;i++){
			fscanf(fp,"%f,",&bytes[i]);
			Xp[k][i+1]=bytes[i];
			//cout<<bytes[i]<<",";
		}
		for(int i=0;i<OutputLength;i++){
			if(i==n){
				Y[k][i]=1;
			}
			else{
				Y[k][i]=0;
			}
		}
		
		
//		save_img(row,column, bytes, n, "train");		

	}
	fclose(fp);
	
	
/////////////////Training Neural Net//////////////////////////////

	
	int err=train( X, Y, theta1, theta2);

	
/////////////////Testing Neural Net//////////////////////////////
	float eff=predict( Xp, Yp, theta1, theta2);
	
	cout<<"\nEfficiency:"<<eff;
		
	return 0;
}


