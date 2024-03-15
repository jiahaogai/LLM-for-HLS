
 #pragma ACCEL kernel

void kernel_jacobi_1d(int tsteps,int n,double A[120],double B[120])
{
  int t;
  int i;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (t = 0; t < 3 1;
        B[i] = 0.33333 * (A[i] + A[i - 1] + A[i + 1]);
      }
    }
    
#pragma endscop
//#pragma endscop
}
