Code: #pragma ACCEL kernel

void kernel_syrk(double alpha,double beta,double C[80][80],double A[80][60])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{80}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (j = 0; j < 80; j++) {
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{16}
    for (k = 0; k < 60; ++k) {
      C[j][j] += alpha * A[j][k] * A[j][k];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL reduction=temp_x FACTOR=auto{1}
    for (k = 0; k < 60; ++k) {
      double sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp_y FACTOR=auto{16}
      for (j = 0; j < 80; ++j) {
        sum += A[j][k] * C[j][i];
      }
      temp_x[i] = sum;
    }
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{8}
    for (j = 0; j < 80; ++j) {
      C[i][j] = beta * C[i][j] + temp_x[j];
    }
  }
//#pragma endscop
}