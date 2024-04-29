Code: ###kernel_xsmm
 #pragma ACCEL kernel

void kernel_xsmm(double alpha,double beta,double C[200][240],double A[200][200],double B[200][240])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 240; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{80}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 200; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{2}
      for (j = 0; j < 240; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
//#pragma endscop
}
Error: 
Please check the code and try again.
Code: ###kernel_row_stream
 #pragma ACCEL kernel

void kernel_row_stream(int n,int m,int k,double A[200][200],double B[200][200],double C[200][200])
{
  int i;
  int j;
  int k_;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 200; j++) {
      C[i][j] = 0.0;
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{1}
      for (k_ = 0; k_ < 200; ++k_) {
        C[i][j] += A[i][k_] * B[k_][j];
      }
    }
  }
//#pragma endscop
}