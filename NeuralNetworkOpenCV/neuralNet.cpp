#include<iostream>
#include<string>
#include <opencv2/opencv.hpp>
#include <cv.h>
#include <highgui.h>
#include <opencv2/ml.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/core/ocl.hpp>

using namespace std;
using namespace cv;


typedef struct {
	int type=0;
	vector<float*> stream;
} sample;

int fIndex[10];

int save_img(int row,int column, float *bytes, int n, string folder){
	string filetype=".png";
	string folderloc="./";
	string filename=std::to_string(n);
	string ind=std::to_string(fIndex[n]);
	string address=folderloc+folder+'/'+filename+'/'+filename+"_"+ind+filetype;
	cout<<address<<endl;
	Mat image(row,column, CV_32FC1, bytes);
//	imwrite( address, image);
//	namedWindow(filename);
	imshow( filename, image);
//	waitKey(0);
	fIndex[n]++;

	return 0;
}
	
vector<int> NeuralNet(cv::Mat& trainingData, cv::Mat& trainingClasses, cv::Mat& testData, cv::Mat& testClasses){
	Ptr<ml::ANN_MLP> mlp = ml::ANN_MLP::create();
	
	//Define parameters
//	CvTermCriteria criteria;
//	criteria.max_iter=1000;
//	criteria.epsilon=0.0001f;
//	criteria.type= CV_TERMCRIT_ITER | CV_TERMCRIT_EPS;
	TermCriteria criteria(TermCriteria::COUNT+TermCriteria::EPS,10000,0.00001f);
//	TermCriteria criteria(TermCriteria::EPS,100000,0.0001f);
	mlp->setTermCriteria(criteria);
	
	
//	CvANN_MLP_TrainParams params;
//	params.train_method = ml::ANN_MLP_TrainParams::BACKPROP;
//	params.bp_dw_scale=0.05f;
//	params.bp_moment_scale=0.05f;
//	params.term_crit=criteria;
	mlp->setTrainMethod(ml::ANN_MLP::BACKPROP, 0.1, 0.1);
	
	
	Mat layers=Mat(2, 1, CV_32SC1);
	layers.row(0)=Scalar(trainingData.cols);
//	layers.row(1)=Scalar(2*trainingData.cols);	
	layers.row(1)=Scalar(10);
	
//	mlp.create(layers);
	mlp->setLayerSizes(layers);
//	mlp->setActivationFunction(ml::ANN_MLP::SIGMOID_SYM);
	mlp->setActivationFunction(ml::ANN_MLP::SIGMOID_SYM);
	bool trained=0;
//	mlp.train(trainingData, trainingClasses, cv::Mat(), cv::Mat(), params);
	cout<<"Training started\n";
	try{
		trained=mlp->train(trainingData, ml::SampleTypes::ROW_SAMPLE,trainingClasses);
	}catch( const std::exception& e ){
		cout<<"Training Error:"<<endl<<"DataSize:"<<trainingData.cols<<endl<<"LabelSize:"<<trainingClasses.cols<<endl<<e.what();
	}
	cout<<"Training ended\n";
	if(trained){
		cout<<"Training Successful\n";
		mlp->save("Model.xml");
	}
	
	vector<int> results;
	for(int i=0;i<testClasses.rows;i++) {
		int maxIndex=0;
		double max=0,net=0;
		Mat response(1,10,CV_32FC1);
		Mat sample=testData.row(i);
		try{
			mlp->predict(sample, response);
		}catch( const std::exception& e ){
			cout<<"Predict Error:"<<endl<<e.what();
		}
		cout<<"Predict complete:"<<response;
		//max=response.at(0,1);
		
		
		max=response.at<float>(0,0);
		//cout<<"First:"<<max<<endl;
		//max=0.0f;
		for(int j=0;j<10;j++){
			net=response.at<float>(0,j);
			if(max<net){
				max=net;
				maxIndex=j;
			}
			
		}
		cout<<" Result:"<<maxIndex<<endl;
		results.push_back(maxIndex);
	}
	return results;
}
	


int main(){
	int n;
	int trainSamples=60000;
	int testSamples=10000;
	int row=28;
	int column=28;
	sample train[10];
	sample test[10];
	int totPix=row*column;
	Mat trainingData(0,totPix,CV_32FC1);
	Mat testData(0,totPix,CV_32FC1);
	Mat trainingClasses(0,1,CV_32FC1);
	Mat testClasses(0,1,CV_32FC1);
	
	cv::ocl::setUseOpenCL(true);
	
	
	vector<int> testClass;
	FILE *fp;
	fp=fopen("mnist_train.csv","r");
	for(int k=0;((k<trainSamples)&&(!feof(fp)));k++){
		fscanf(fp,"%d,",&n);
		//cout<<"Running:"<<k<<endl;
		float *bytes=(float *)calloc(totPix,sizeof(float));
		for(int i=0;i<totPix;i++){
			fscanf(fp,"%f,",&bytes[i]);
			//cout<<bytes[i]<<",";
		}
		//save_img(row,column, bytes, n, "train");
		train[n].type=n;
		train[n].stream.push_back(bytes);
		Mat data(1,totPix, CV_32FC1, bytes);
		trainingData.push_back(data);
		float *nt=(float *)calloc(10,sizeof(float));
		for(int i=0;i<10;i++){
			if(i==n) nt[i]=1; 
			else nt[i]=-1;
			//cout<<bytes[i]<<",";
		}
		
		Mat clas(1,10,CV_32FC1, nt);
		trainingClasses.push_back(clas);
		

	}
	fclose(fp);
	cout<<"Training Sample Size:"<<trainingData.rows<<endl;

	fp=fopen("mnist_test.csv","r");
	for(int k=0;(k<testSamples||(!feof(fp)));k++){
		fscanf(fp,"%d,",&n);
		float *bytes=(float *)calloc(totPix,sizeof(float));
		for(int i=0;i<totPix;i++){
			fscanf(fp,"%f,",&bytes[i]);
			//cout<<bytes[i]<<",";
		}
		//save_img(row,column, bytes, n, "test");
		test[n].type=n;
		test[n].stream.push_back(bytes);
		Mat data(1,totPix, CV_32FC1, bytes);
		testData.push_back(data);
		float *nt=(float *)calloc(10,sizeof(float));
		for(int i=0;i<10;i++){
			if(i==n) nt[i]=1; 
			else nt[i]=-1;
			//cout<<bytes[i]<<",";
		}
		
		Mat clas(1,10,CV_32FC1, nt);
		testClasses.push_back(clas);
		testClass.push_back(n);

	}
	
	fclose(fp);
	
	vector<int> res=NeuralNet(trainingData, trainingClasses, testData, testClasses);
	int eff=0;
	for(int i=0;i<res.size();i++){
		if(res.at(i)==testClass.at(i)){
			eff++;
		}
	}
	float per=eff/(float)res.size();
	cout<<"\nEfficiency:"<<per<<endl;
	
	return 0;
}


