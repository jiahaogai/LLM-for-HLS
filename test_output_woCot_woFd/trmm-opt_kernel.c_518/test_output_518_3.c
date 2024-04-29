#pragma ACCEL kernel

void kernel_trmm()
{
  int i;
  int j;
  int k;
  int k_col;
  double sum;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{80}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{60}
      for (k = 0; k < 60; k++) {
        k_col = i * 60 + k;
        sum += A[k_col][j] * B[k_col][j];
      }
      C[i][j] = sum;
    }
  }
//#pragma endscop
}