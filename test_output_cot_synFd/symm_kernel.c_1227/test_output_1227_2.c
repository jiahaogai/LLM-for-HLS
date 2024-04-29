Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{4}
    for (j = 0; j < 60; j++) {
      temp1[j] = 0.0;
      double sum = 0.0;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{20}
      for (k = 0; k < 80; ++k) {
        sum += A[i][k] * B[k][j];
      }
      temp1[j] = sum;
    }
    
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      temp2[j] = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{4}
      for (k = 0; k < 60; ++k) {
        temp2[j] += alpha * A[i][k] * temp1[k];
      }
      temp2[j] += beta * C[i][j];
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      C[i][j] = temp2[j];
    }
  }
//#pragma endscop
}