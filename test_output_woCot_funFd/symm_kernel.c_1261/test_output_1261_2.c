#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double temp_x;
  double temp_y;
  double temp2;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{5}
  outer:
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    middle:
    for (j = 0; j < 80; j++) {
      temp2 = 0.0;
      
#pragma ACCEL PARALLEL reduction = temp2 FACTOR=auto{1}
      inner:
      for (k = 0; k < 60; k++) {
        temp_x = alpha * A[i][k];
        temp_y = B[k][j];
        temp2 += temp_x * temp_y;
      }
      C[i][j] += temp2 * beta;
    }
  }
}