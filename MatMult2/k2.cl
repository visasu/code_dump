__kernel void MatMult(__global float4* A, __global float4* B, __global float4* C){
	//Computes C= A *(B');
	uint KerDim1=5,KerDim2=10,KerDim3=10,WorkDim=10;
	//ColB = ColB1 * ColB2
	uint localId0=get_local_id(0);//Range[0-(KerDim1-1)]
	uint localId1=get_local_id(1);//Range[0-(KerDim2-1)]
	uint localId2=get_local_id(2);//Range[0-(KerDim3-1)]
	uint groupId0=get_group_id(0);//Range[0-(WorkDim1-1)]//workgroup dimension0
/*
//	printf("in=<%ud,>\n",localId0);
	barrier(CLK_GLOBAL_MEM_FENCE);
	
	//both Mat1, Mat2 should be row major
	int index=localId1 + (localId2 * KerDim1) + (localId0 * KerDim1 * KerDim2);
	
	float b=B[index];
	float a=A[localId1 + (localId2 * KerDim2) + (groupId0 * KerDim2 * KerDim3)];
//	temp[index] = B[index]* A[localId1 + (localId2 * KerDim2) + (groupId0 * KerDim2 * KerDim3)];
	temp[index] = b * a;
	barrier(CLK_LOCAL_MEM_FENCE);
	printf("in=<%f,>\n",b);
*/							 
	if((localId1 == 0) && (localId2 == 0)){
		float tsum=0;
		int i=0;
/*		for(i=0;i<(KerDim2 * KerDim3); i++){
			tsum += temp[i + (localId0 * KerDim2 * KerDim3)];
		}
*/		
	C[localId0 + (0 * KerDim1)].s0 = 2.0f;
	C[localId0 + (0 * KerDim1)].s1 = 2.0f;
	C[localId0 + (0 * KerDim1)].s2 = 2.0f;
	C[localId0 + (0 * KerDim1)].s3 = 2.0f;

	}

//	barrier(CLK_GLOBAL_MEM_FENCE);
}
