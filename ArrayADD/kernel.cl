__kernel void vecAdd(__global float* A, __global float* B, __global float* C){
	//Computes C= A + B;
	uint localId0=get_local_id(0);//Range[0-(KerDim1-1)]
	uint localId1=get_local_id(1);//Range[0-(KerDim2-1)]
	uint localId2=get_local_id(2);//Range[0-(KerDim3-1)]
	uint groupId0=get_group_id(0);//Range[0-(WorkDim1-1)]//workgroup dimension0
	uint globalId=get_global_id(0);
	float localA=A[globalId];
	float localB=B[globalId];
	float localC=localA+localB;
	C[globalId]=localC;
	//Somehow it seems that CLK_GLOBAL_MEM_FENCE is causing problem. Not sure why though. 
//	barrier(CLK_GLOBAL_MEM_FENCE);

}
