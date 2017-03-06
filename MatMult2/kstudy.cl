//Kernel to do matrix multiply of X and Y. Single workgroup, Z mat dimension as NDRange(RowZ, ColZ)
__kernel void MatMult(__global float* A, __global float* B, __global float* C, __local float* temp){
	//Computes C= A *(B');
	uint KerDim1=5,KerDim2=10,KerDim3=10,WorkDim=10;
	//ColB = ColB1 * ColB2
	uint localId0=get_local_id(0);//Range[0-(KerDim1-1)]
	uint localId1=get_local_id(1);//Range[0-(KerDim2-1)]
	uint localId2=get_local_id(2);//Range[0-(KerDim3-1)]
	uint groupId0=get_group_id(0);//Range[0-(WorkDim1-1)]//workgroup dimension0
	uint globalId0=get_global_id(0);
	uint globalId1=get_global_id(1);
	uint globalId2=get_global_id(2);
	uint noRowZ=get_global_size(0);
	uint noColZ=get_global_size(1);
	uint noColX=get_global_size(2);
	printf("<F:%u %u %u>",globalId0,globalId1,globalId2);
	C[globalId0+globalId1*noRowZ]=0;
	barrier(CLK_GLOBAL_MEM_FENCE);

}
