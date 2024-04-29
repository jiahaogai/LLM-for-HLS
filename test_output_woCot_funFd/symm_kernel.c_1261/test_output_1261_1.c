#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double temp1;
  double temp2;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{5}
  outer:
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 80; j++) {
      temp1 = 0.0;
      
#pragma ACCEL PARALLEL reduction = temp1 FACTOR=auto{2}
      inner:
      for (k = 0; k < 60; k++) {
        temp1 += A[i][k] * B[k][j];
      }
      temp2 = 0.0;
      
#pragma ACCEL PARALLEL reduction = temp2 FACTOR=auto{2}
      inner_1:
      for (k = 0; k < 60; k++) {
        temp2 += A[k][i] * B[k][j];
      }
      C[i][j] = (((alpha * temp1) + (beta * temp2)) + C[i][j]);
    }
  }
}