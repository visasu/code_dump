#include<iostream>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include<cstdio>
#include<fstream>
#include<CL/cl.hpp>
#include<sstream>
#include<string>


using namespace std;


int main(){

	int RowX = 10;
	int ColX = 10;
	int RowY = 10;
	int ColY = 10;
	int RowZ = 10;
	int ColZ = 10;
	
	float X[RowX][ColX];
	float Y[RowY][ColY];
	float Z[RowZ][ColZ];
	cout<<sizeof(X)<<endl<<endl;
	
	
	for(int i=0;i<RowX;i++){
		for(int j=0;j<ColX;j++){
			X[i][j]=1;
		}
	}
	for(int i=0;i<RowY;i++){
		for(int j=0;j<ColY;j++){
			Y[i][j]=2;
		}
	}
	
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
	cl::Platform default_platform=all_platforms.at(1);
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
	ifstream ifs("k3.cl");
	kernel_code.assign((istreambuf_iterator<char>(ifs)),(std::istreambuf_iterator<char>()));
	source.push_back({kernel_code.c_str(), kernel_code.length()});
	
	cl::Program program(context, source);
	if(program.build({default_device})<0){
		cout<<"Error building:"<<program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device)<<"\n";
		exit(1);
	}
	cout<<"\nAllocating Buffers\n";
	/////////////Allocating Buffers on Device////////////////////////

	cl::Buffer buffer_X(context,CL_MEM_READ_WRITE, sizeof(X));
	cl::Buffer buffer_Y(context,CL_MEM_READ_WRITE, sizeof(Y));
	cl::Buffer buffer_Z(context,CL_MEM_READ_WRITE, sizeof(Z));
	
/*	
	cl::Buffer buffer_X(context,CL_MEM_READ_ONLY, RowX*ColX*sizeof(float));
	cl::Buffer buffer_Y(context,CL_MEM_READ_ONLY, RowY*ColY*sizeof(float));
	cl::Buffer buffer_Z(context,CL_MEM_READ_WRITE, RowX*RowY*sizeof(float));
	cl::Buffer buffer_temp(context,CL_MEM_READ_WRITE, RowY*ColY*sizeof(float));
	cl::Buffer buffer_RowX(context,CL_MEM_READ_ONLY, sizeof(int));
	cl::Buffer buffer_RowY(context,CL_MEM_READ_ONLY, sizeof(int));
	cl::Buffer buffer_ColY1(context,CL_MEM_READ_ONLY, sizeof(int));
	cl::Buffer buffer_ColY2(context,CL_MEM_READ_ONLY, sizeof(int));
*/	
	/////////////Creating Queue////////////////////////
	cout<<"\nCreating Queue\n";
	cl::CommandQueue queue(context, default_device);
	
	/////////////Writing Input Buffers////////////////////////
	cout<<"\nEnqueue X, Y\n";
	queue.enqueueWriteBuffer(buffer_X,CL_TRUE | CL_QUEUE_PROFILING_ENABLE,0,sizeof(X),&X);
	queue.enqueueWriteBuffer(buffer_Y,CL_TRUE | CL_QUEUE_PROFILING_ENABLE,0,sizeof(Y),&Y);
/*	queue.enqueueWriteBuffer(buffer_RowX,CL_TRUE | CL_QUEUE_PROFILING_ENABLE,0,sizeof(int),&RowX);
	queue.enqueueWriteBuffer(buffer_RowY,CL_TRUE | CL_QUEUE_PROFILING_ENABLE,0,sizeof(int),&RowY);
	queue.enqueueWriteBuffer(buffer_ColY1,CL_TRUE | CL_QUEUE_PROFILING_ENABLE,0,sizeof(int),&ColY1);
	queue.enqueueWriteBuffer(buffer_ColY2,CL_TRUE | CL_QUEUE_PROFILING_ENABLE,0,sizeof(int),&ColY2);
*/
	//queue.enqueueWriteBuffer(buffer_act2,CL_TRUE | CL_QUEUE_PROFILING_ENABLE,0,Layer_2_Size*sizeof(float),act2);
	queue.enqueueBarrierWithWaitList();
	
	cl::Kernel kernel=cl::Kernel(program,"MatMult");
	kernel.setArg(0, buffer_X);
	kernel.setArg(1, buffer_Y);
	kernel.setArg(2, buffer_Z);
/*	kernel.setArg(3, buffer_temp);
	kernel.setArg(4, buffer_RowX);
	kernel.setArg(5, buffer_RowY);
	kernel.setArg(6, buffer_ColY1);
	kernel.setArg(7, buffer_ColY2);
*/	

	/////////////Starting Kernel////////////////////////
	cout<<"\nStarting Kernel\n";

	queue.enqueueNDRangeKernel(kernel,cl::NullRange,cl::NDRange(RowX * ColX),cl::NDRange(RowX * ColX));
	queue.enqueueBarrierWithWaitList();
	/////////////Reading Output Buffer////////////////////////
	cout<<"\nReading Output Z\n";
	
	queue.enqueueReadBuffer(buffer_Z, CL_TRUE,0,sizeof(Z),&Z);
	queue.finish();
	cout<<endl<<"X:"<<endl;
	for(int i=0;i<RowX;i++){
		for(int j=0;j<ColX;j++){
			cout<<X[i][j]<<",";
		}
		cout<<endl;
	}
	cout<<endl<<"Y:"<<endl;
	for(int i=0;i<RowY;i++){
		for(int j=0;j<ColY;j++){
			cout<<Y[i][j]<<",";
		}
		cout<<endl;
	}
	cout<<endl<<"Z:"<<endl;
	for(int i=0;i<RowX;i++){
		for(int j=0;j<RowY;j++){
			cout<<Z[i][j]<<",";
		}
		cout<<endl;
	}
	
	return 0;

}
