Code: #pragma ACCEL kernel

void kernel_syr2k(int n,double alpha,double beta,double C[4096],double A[4096],double B[4096])
{
  int i;
  int j;
  int k;
  int k_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{240}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j <= i; j++) {
      k_col = 0;
      while (k_col < 64) {
        mult = alpha * A[i * 64 + k_col] * B[k_col * 64 + j];
        C[i * 64 + k_col] += mult;
        C[j * 64 + k_col] += mult * beta;
        ++k_col;
      }
      C[j * 64 + j] += alpha * (double )sum_elements(A, j * 64, j * 64 + 64) * (double )sum_elements(B, j * 64, j * 64 + 64);
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_trmm(int n,double alpha,double B[4096],double A[4096])
{
  int i;
  int j;
  int k;
  int k_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = i; j < 64; j++) {
      k_col = 0;
      while (k_col < 64) {
        mult = alpha * A[j * 64 + k_col];
        B[j * 64 + k_col] *= mult;
        k_col++;
      }
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_trsm(int n,double alpha,double B[4096],double A[4096])
{
  int i;
  int j;
  int k;
  int k_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = i; j < 64; j++) {
      k_col = 0;
      while (k_col < 64) {
        mult = alpha * A[j * 64 + k_col];
        B[j * 64 + k_col] *= mult;
        k_col++;
      }
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL kernel