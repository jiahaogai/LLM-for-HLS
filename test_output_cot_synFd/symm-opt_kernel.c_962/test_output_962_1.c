Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int m;
  int n;
  int p;
  double temp1;
  double temp2;
  int i;
  int j;
  int k;
  int invoke_symm;
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{15}
  invoke_symm = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  if (invoke_symm == 0) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (i = 0; i < 60; i++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{1}
      for (j = 0; j < 80; j++) {
        temp1 = 0.0;
        
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{16}
        for (k = 0; k < 60; ++k) {
          temp1 += A[i][k] * B[k][j];
        }
        C[i][j] += temp1;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  invoke_symm = 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  if (invoke_symm == 1) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (i = 0; i < 60; i++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{1}
      for (j = 0; j < 80; j++) {
        temp2 = 0.0;
        
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{__PARA__L3}
        for (k = 0; k < 60; ++k) {
          temp2 += A[k][i] * B[k][j];
        }
        C[i][j] = alpha * temp2 + beta * C[i][j];
      }
    }
  }
  
#pragma endscop
}