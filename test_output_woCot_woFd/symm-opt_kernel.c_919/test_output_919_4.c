#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{12}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (j = 0; j < 80; j++) {
      double temp_1 = 0.0;
      
#pragma ACCEL PARALLEL reduction = temp_1 FACTOR=auto{4}
      for (k = 0; k < 60; k++) {
        k_col = 60 * k + j;
        mult = alpha * A[i][k] * B[k][j_col];
        temp_1 += mult;
      }
      C[i][j_col] = temp_1 + beta * C[i][j_col];
    }
  }
}