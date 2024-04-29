#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int r;
  int q;
  int p;
  int s;
  double temp_x;
  double temp_y;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (p = 0; p < 60; p++) {
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
    for (s = 0; s < 80; s++) {
      temp_x = 0.0;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL reduction=temp_x FACTOR=auto{1}
      for (q = 0; q < 60; q++) {
        temp_y = A[p][q] * B[q][s];
        temp_x = temp_x + temp_y;
      }
      C[p][s] = temp_x;
    }
  }
}