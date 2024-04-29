#pragma ACCEL PIPELINE auto{}
#pragma ACCEL TILE FACTOR=auto{2}
#pragma ACCEL PARALLEL FACTOR=auto{10}
void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{4}
      for (j = 0; j < 80; j++) {
        double temp1 = 0.0;
        
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{4}
        for (long long n = 0LL; n < 60LL; n++) {
          temp2[0] += A[i][n] * B[n][j];
        }
        for (long long n = 0LL; n < 40LL; n++) {
          temp1 += temp2[n] * A[k][n];
        }
        C[i][j] += temp1;
      }
    }
  }
//#pragma endscop
}