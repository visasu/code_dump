
inline float sigm(float x);

__kernel void RandInit(__global float4 *Theta1, __global float4 *Theta2){
	uint global_addr=get_global_id(0);
	Theta1[global_addr].s0=global_addr*0.001f;
	Theta1[global_addr].s1=global_addr*0.001f;
	Theta1[global_addr].s2=global_addr*0.001f;
	Theta1[global_addr].s3=global_addr*0.001f;
	if (global_addr<280){
		Theta2[global_addr].s0=global_addr*0.01f;
		Theta2[global_addr].s1=global_addr*0.01f;
		Theta2[global_addr].s2=global_addr*0.01f;
		Theta2[global_addr].s3=global_addr*0.01f;
	}
	barrier(CLK_GLOBAL_MEM_FENCE);

}
__kernel void Layer1(__global float4* X, __global float4* Theta1, __local float* temp, __global float* act2){
	//Considering the bias term will come at last element of each row in X
	int localId0=get_local_id(0);//Range[0-195]
	int localId1=get_local_id(1);//Range[0-239]
	int localId2=get_local_id(2);//Range[0-249]
	int actNo=get_group_id(0);//Range[0-27]
	int index=localId0+localId1*196+localId2*196*240;

	if(actNo<27){

		float4 theta=Theta1[localId0+actNo*196];
		float4 x=X[index+actNo*60000];

		temp[index+actNo*60000]=dot(theta,x);

		barrier(CLK_LOCAL_MEM_FENCE);


		if(localId0==0){
			act2[localId1+localId2*240+actNo*60000]=0;
			for(int i=0;i<196;i++){
				act2[localId1+localId2*240+actNo*60000] +=temp[i+localId1*196+localId2*196*240+actNo*60000];
			}
			act2[localId1+localId2*240+actNo*60000] = sigm(act2[localId1+localId2*240+actNo*60000]);
		}
	}
	else{
		act2[localId1+localId2*240+27*60000] = 1; //Bias unit at last end of matrix
	}
	barrier(CLK_GLOBAL_MEM_FENCE);
	
}
__kernel void Layer2(__global float4* act2, __global float4* Theta2, __global float* temp, __global float* act3){
	//Considering the bias term will come at last element of each row in X
	int localId0=get_local_id(0);//Range[0-6]->28/4
	int localId1=get_local_id(1);//Range[0-239]
	int localId2=get_local_id(2);//Range[0-249]
	int actNo=get_group_id(0);//Range[0-9]->Output Layer Size =10
	int index=localId0+localId1*7+localId2*7*240;


		float4 theta=Theta2[localId0+actNo*7];
		float4 x=act2[index+actNo*60000];

		temp[index+actNo*60000]=dot(theta,x);

		barrier(CLK_LOCAL_MEM_FENCE);


	if(localId0==0){
		act3[localId1+localId2*240+actNo*60000]=0;
		for(int i=0;i<7;i++){
			act3[localId1+localId2*240+actNo*60000] +=temp[i+localId1*7+localId2*7*240+actNo*60000];
		}
		act3[localId1+localId2*240+actNo*60000] = sigm(act3[localId1+localId2*240+actNo*60000]);
	}
	barrier(CLK_GLOBAL_MEM_FENCE);
	
}

__kernel void MatMult(__global float* A, __global float* B, __global float* C, __local float* temp, __global int *RowA, __global int *RowB, __global int *ColB1, __global int *ColB2){
	//Computes C= A *(B');
	const int KerDim1=RowB,KerDim2=ColB1,KerDim3=ColB2,WorkDim=RowA;
	//ColB = ColB1 * ColB2
	int localId0=get_local_id(0);//Range[0-(KerDim1-1)]
	int localId1=get_local_id(1);//Range[0-(KerDim2-1)]
	int localId2=get_local_id(2);//Range[0-(KerDim3-1)]
	
	int groupId0=get_group_id(0);//Range[0-(WorkDim1-1)]//workgroup dimension0
	//both Mat1, Mat2 should be row major
	int index=localId1 + (localId2 * KerDim1) + (localId0 * KerDim1 * KerDim2);
	
	temp[index] = B[index] * A[localId1 + (localId2 * KerDim2) + (groupId0 * KerDim2 * KerDim3)];
	
	float tsum;
	int i=0;
							 
	if((localId1 == 0) && (localId2 == 0)){
		for(i=0;i<(KerDim2 * KerDim3); i++){
			tsum += temp[i + (localId0 * KerDim2 * KerDim3)];
		}
		C[localId0 + (groupId0 * KerDim1)] = tsum;
	}

	barrier(CLK_GLOBAL_MEM_FENCE);
}
	
		

__kernel void Backprop1(__global float* Y, __global float* act3, __local float* temp, __global float* d3){
	int localId0=get_local_id(0);//Range[0-9]
	int localId1=get_local_id(1);//Range[0-239]
	int localId2=get_local_id(2);//Range[0-249]
	int groupId0=get_group_id(0);//Range[0]->only one workgroup needed
	int index=localId0+localId1*10+localId2*10*240;
	
	d3[index]=act3[index]-Y[index];
	barrier(CLK_GLOBAL_MEM_FENCE);
}
__kernel void Backprop2(__global float* d3, __global float* act2, __local float* temp, __global float* diffD){
	//temp size should be 28*60,000;
	int localId0=get_local_id(0);//Range[0-27]
	int localId1=get_local_id(1);//Range[0-239]
	int localId2=get_local_id(2);//Range[0-249]
	
	int groupId0=get_group_id(0);//Range[0-9]->only one workgroup needed
	int index=localId0+localId1*10+localId2*10*240;
	
	temp[index]=act2[index]*d3[;
	
	barrier(CLK_GLOBAL_MEM_FENCE);
}

__kernel void Backprop1(__global float* Y, __global float* act3, __local float* temp, __global float* d3){
	int localId0=get_local_id(0);//Range[0-9]
	int localId1=get_local_id(1);//Range[0-239]
	int localId2=get_local_id(2);//Range[0-249]
	int groupId0=get_group_id(0);//Range[0-27]
	int index=localId0+localId1*10+localId2*10*240;
	
	d3[index]=act3[index]-Y[index];
	barrier(CLK_GLOBAL_MEM_FENCE);
}
	
	
__kernel void BackProp(__global float* Y, __global float* act3, __global float* Theta2, __global float* act2, __local float* temp, __global float* Theta1){
	int localId0=get_local_id(0);//Range[0-9]
	int localId1=get_local_id(1);//Range[0-239]
	int localId2=get_local_id(2);//Range[0-249]
	int groupId0=get_group_id(0);//Range[0-27]
	int index=localId0+localId1*10+localId2*10*240;
//Start here--------------------------------------------------
	float d3=act3[index]-Y[index];
	temp[index]=Theta2[localId0+groupId0*10]*d3;
	temp[index]=temp[index]*act2[index]*(1-act2[index]);
	barrier(CLK_LOCAL_MEM_FENCE);
	//Need to add all the id0s[0-9] in each group. combination step for matrix multiply
	if(localId0==0){
		float t=0;
//		act2[localId1+localId2*240+groupId0*60000]=0;
		for(int i=0;i<10;i++){
			t +=temp[i+localId1*10+localId2*10*240+groupId0*60000];
		}
		temp[localId1+localId2*240+groupId0*60000] = sigm(t);
	}

	barrier(CLK_LOCAL_MEM_FENCE);
	
	
	



	if(actNo<27){

		float4 theta=Theta1[localId0+actNo*196];
		float4 x=X[index+actNo*60000];

		temp[index+actNo*60000]=dot(theta,x);

		barrier(CLK_LOCAL_MEM_FENCE);


		if(localId0==0){
			act2[localId1+localId2*240+actNo*60000]=0;
			for(int i=0;i<196;i++){
				act2[localId1+localId2*240+actNo*60000] +=temp[i+localId1*196+localId2*196*240+actNo*60000];
			}
			act2[localId1+localId2*240+actNo*60000] = sigm(act2[localId1+localId2*240+actNo*60000]);
		}
	}
	else{
		act2[localId1+localId2*240+27*60000] = 1; //Bias unit at last end of matrix
	}
	barrier(CLK_GLOBAL_MEM_FENCE);
	
	
	
	
}
__kernel void Test(__global float* Xp, __global float* Theta1, __global float* temp, __global float* Theta2, __global float* Y){}

inline float sigm(float x){
	return 1.0f/(1.0f+exp(-1.0f*x));
}
inline float sigmGrad(float x){
	return (sigm(x)*(1-sigm(x)));
}
	