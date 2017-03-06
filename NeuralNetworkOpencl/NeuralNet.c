#include<iostream>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include<cstdio>
#include<fstream>
#include<CL/cl.hpp>
#include<sstream>
#include<string>


#define trainSamples 60000
#define testSamples 10000
#define OutputLength 10
#define ROW 28
#define COL 28
#define Layer_1_Size ROW*COL+1
#define Layer_2_Size 28
#define Theta1SIZE (Layer_2_Size-1)*Layer_1_Size
#define Theta2SIZE OutputLength*Layer_2_Size
#define XSIZE trainSamples*Layer_1_Size
#define YSIZE trainSamples*OutputLength
#define XpSIZE testSamples*Layer_1_Size
#define YpSIZE testSamples*OutputLength


using namespace std;

float X[trainSamples][Layer_1_Size];
float Y[trainSamples][OutputLength];
float Theta1[Layer_2_Size-1][Layer_1_Size];
float Theta2[OutputLength][Layer_2_Size];


int main(){
	
	////////////Finding Platforms/////////////////////
	vector<cl::Platform> all_platforms;
	cl::Platform::get(&all_platforms);
	if(all_platforms.size()==0){
		cout<<"No platform found!!\n";
		exit(1);
	}
	cout<<"Available Platforms:\n";
	for(cl::Platform a: all_platforms){
		cout<<a.getInfo<CL_PLATFORM_NAME>()<<"\n";;
	}
	cl::Platform default_platform=all_platforms.at(0);
	cout<<"Using Platform:"<<default_platform.getInfo<CL_PLATFORM_VERSION>()<<"\n";
	
	///////////Finding Devices////////////////////////
	vector<cl::Device> all_devices;
	default_platform.getDevices(CL_DEVICE_TYPE_ALL,&all_devices);
	if(all_devices.size()==0){
		cout<<"No Devices found!!\n";
		exit(1);
	}
	
	cout<<"Available Devices:\n";
	for(cl::Device a: all_devices){
		cout<<a.getInfo<CL_DEVICE_NAME>()<<"\n";
	}
	cl::Device default_device=all_devices.at(0);
//	cout<<"Using Device:"<<default_device.getInfo<CL_DEVICE_NAME>()<<"\n";
	cout<<"Using Device:"<<default_device.getInfo<CL_DEVICE_NAME>()<<"\n";
	vector<size_t> n=default_device.getInfo<CL_DEVICE_MAX_WORK_ITEM_SIZES>();
	
	cout<<"Available size: (";
	for(size_t k: n){
		cout<<k<<",";
	}
	cout<<")"<<"\n";
	cl::Context context(default_device);//Can use arg (all_devices);
	
	/////////////Read KERNEL FILE////////////////////////
	cl::Program::Sources source;
	string kernel_code;
	ifstream ifs("kernel.cl");
	kernel_code.assign((istreambuf_iterator<char>(ifs)),(std::istreambuf_iterator<char>()));
	source.push_back({kernel_code.c_str(), kernel_code.length()});
	
	cl::Program program(context, source);
	if(program.build({default_device})<0){
		cout<<"Error building:"<<program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device)<<"\n";
		exit(1);
	}
	cout<<"\nAllocating Buffers";
	/////////////Allocating Buffers on Device////////////////////////
	
	cl::Buffer buffer_X(context,CL_MEM_READ_ONLY, XSIZE*sizeof(float));
	cl::Buffer buffer_Y(context,CL_MEM_READ_ONLY, YSIZE*sizeof(float));
	cl::Buffer buffer_temp(context,CL_MEM_READ_ONLY, ACT1SIZE*sizeof(float));
	cl::Buffer buffer_Theta1(context,CL_MEM_READ_WRITE, Theta1SIZE*sizeof(float));//Depends on the dimension of x;
	cl::Buffer buffer_Theta2(context,CL_MEM_READ_WRITE, Theta2SIZE*sizeof(float));//Depends on the dimension of x;
	cl::Buffer buffer_Xp(context,CL_MEM_READ_ONLY, XpSIZE*sizeof(float));
	cl::Buffer buffer_Yp(context,CL_MEM_READ_ONLY, YpSIZE*sizeof(float));
	
	/////////////Creating Queue////////////////////////
	cl::CommandQueue queue(context, default_device);
	
	/////////////Writing Input Buffers////////////////////////
	queue.enqueueWriteBuffer(buffer_X,CL_TRUE | CL_QUEUE_PROFILING_ENABLE,0,XSIZE*sizeof(float),X);
	queue.enqueueWriteBuffer(buffer_Y,CL_TRUE | CL_QUEUE_PROFILING_ENABLE,0,YSIZE*sizeof(float),Y);
	queue.enqueueWriteBuffer(buffer_Xp,CL_TRUE | CL_QUEUE_PROFILING_ENABLE,0,XpSIZE*sizeof(float),Xp);
	queue.enqueueWriteBuffer(buffer_Yp,CL_TRUE | CL_QUEUE_PROFILING_ENABLE,0,YpSIZE*sizeof(float),Yp);
	queue.enqueueWriteBuffer(buffer_Theta1,CL_TRUE | CL_QUEUE_PROFILING_ENABLE,0,Theta1SIZE*sizeof(float),Theta1);
	queue.enqueueWriteBuffer(buffer_Theta2,CL_TRUE | CL_QUEUE_PROFILING_ENABLE,0,Theta2SIZE*sizeof(float),Theta2);

	//queue.enqueueWriteBuffer(buffer_temp,CL_TRUE | CL_QUEUE_PROFILING_ENABLE,0,Layer_2_Size*sizeof(float),temp);
	queue.enqueueBarrierWithWaitList();
	
	cl::Kernel kernel1=cl::Kernel(program,"RandInit");
	kernel1.setArg(0, buffer_Theta1);
	kernel1.setArg(1, buffer_Theta2);

	cl::Kernel kernel2=cl::Kernel(program,"Layer1");
	kernel2.setArg(0, buffer_X);
	kernel2.setArg(1, buffer_Theta1);
	kernel2.setArg(2, buffer_temp);

	cl::Kernel kernel3=cl::Kernel(program,"Layer2");
	kernel3.setArg(0, buffer_temp);
	kernel3.setArg(1, buffer_Theta2);
	kernel3.setArg(2, buffer_Y);

	cl::Kernel kernel4=cl::Kernel(program,"BackProp");
	kernel4.setArg(0, buffer_Theta1);
	kernel4.setArg(1, buffer_temp);
	kernel4.setArg(2, buffer_Theta2);
	kernel4.setArg(3, buffer_Y);

	cl::Kernel kernel5=cl::Kernel(program,"Test");
	kernel5.setArg(0, buffer_Xp);
	kernel5.setArg(1, buffer_Theta1);
	kernel5.setArg(2, buffer_temp);
	kernel5.setArg(3, buffer_Theta2);
	kernel5.setArg(4, buffer_Yp);
	
	//size_t wg_size;
	//int err=cl::Kernel::getWorkGroupInfo(kernel,default_device,CL_KERNEL_WORK_GROUP_SIZE,sizeof(wg_size), &wg_size, NULL);
	
	
//	//kernel.setArg(0, buffer_X);
//	//kernel.setArg(1, buffer_Y);
	//kernel.setArg(2, buffer_Theta1);
	//kernel.setArg(3, buffer_Theta2);
	//kernel.setArg(4, buffer_temp);
	//cout<<"Data Size:"<<SIZE<<endl;
	/////////////Starting Kernel////////////////////////
	queue.enqueueNDRangeKernel(kernel1,cl::NullRange,cl::NDRange(XSIZE),cl::NullRange);
//	queue.enqueueNDRangeKernel(kernel2,cl::NullRange,cl::NDRange(YSIZE),cl::NullRange);
//	queue.enqueueNDRangeKernel(kernel3,cl::NullRange,cl::NDRange(trainSamples*Layer_2_Size),cl::NullRange);
//	queue.enqueueNDRangeKernel(kernel4,cl::NullRange,cl::NDRange(trainSamples*Layer_2_Size),cl::NullRange);
	
	/////////////Reading Output Buffer////////////////////////
	queue.enqueueReadBuffer(buffer_Theta1, CL_TRUE,0,Theta1SIZE*sizeof(float),Theta1);
	queue.enqueueReadBuffer(buffer_Theta2, CL_TRUE,0,Theta2SIZE*sizeof(float),Theta2);

	for(int i=0;i<OutputLength;i++){
		for(int j=0;j<Layer_2_Size;j++){
			cout<<Theta2[i][j]<<endl;
		}
	}
	queue.finish();

}
