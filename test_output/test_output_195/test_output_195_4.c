
- Use the following pragmas to offload the code to FPGA 
 #pragma ACCEL POFFLOAD FACTOR=auto{1}

 #pragma ACCEL PARALLEL FACTOR=auto{1}

/* DCE code. Must scan the entire live-out data.
   Can be excluded if one writes all live-out points.
   Also ignore registration in the code below. */
 #pragma ACCEL POINT PARAMS=flp
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{30}
  
#pragma ACCEL PARALLEL FACTOR=auto{12}
void kernel_jacobi_1d(int tsteps,int n,double A[120],double B[120])
{
  int t;
  int i;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (t = 0; t < 40; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{30}
    for (i = 1; i < 120 - 1; i++) {
      B[i] = 0.33333 * (A[i - 1] + A[i] + A[i + 1]);
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{12}
    for (i = 1; i < 120 - 1; i++) {
      A[i] = 0.33333 * (B[i - 1] + B[i] + B[i + 1]);
    }
  }
//#pragma endscop
}
