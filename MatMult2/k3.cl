__kernel void MatMult(__global float* A, __global float* B, __global float* C){
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

	printf("in=<%u,%u,%u>\n",localId0, localId1, localId2);
	printf("gl=<%u,%u,%u>\n",globalId0, globalId1, globalId2);
	C[globalId0+10*globalId1]=A[globalId0+10*globalId1]+B[globalId0+10*globalId1];
		
}
