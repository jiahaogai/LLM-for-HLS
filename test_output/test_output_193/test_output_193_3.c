
 #pragma ACCEL kernel

void kernel_jacobi_2d(int tsteps,int n,double A[90][90],double B[90][90])
{
  int t;
  int i;
  int j;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (t = 0; t < 3{
      B[i][j] = 0.2 * (A[i][j] + A[i][j - 1] + A[i][1 + j] + A[i - 1][j] + A[i - 1][j - 1] + A[i - 1][1 + j]);
    }
  }
//#pragma endscop
}
