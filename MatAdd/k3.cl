__kernel void MatMult(__global float4* A, __global float4* B, __global float4* C){
	//Computes C= A *(B');
	uint KerDim1=5,KerDim2=10,KerDim3=10,WorkDim=10;
	//ColB = ColB1 * ColB2
	uint localId0=get_local_id(0);//Range[0-(KerDim1-1)]
	uint localId1=get_local_id(1);//Range[0-(KerDim2-1)]
	uint localId2=get_local_id(2);//Range[0-(KerDim3-1)]
	uint groupId0=get_group_id(0);//Range[0-(WorkDim1-1)]//workgroup dimension0
	uint globalId=get_global_id(0);

//	printf("in=<%ud,>\n",localId0);
	if (globalId<100)
		C[globalId]=A[globalId]+B[globalId];
}
