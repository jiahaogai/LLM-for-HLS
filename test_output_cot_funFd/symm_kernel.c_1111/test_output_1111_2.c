#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{12}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{11}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{10}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{4}
      for (j = 0; j < 80; j++) {
        double temp2 = 0.0;
        double temp1 = 0.0;
        int _in_j;
        int _in_k;
        for (_in_j = 0; _in_j < 60; _in_j++) {
          _in_k = _in_j;
          temp1 = A[_in_j][k];
          #pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{1}
          for (_in_k = _in_k; _in_k < 80; _in_k++) {
            temp2 += temp1 * B[_in_k][j];
          }
        }
        C[i][j] += temp2;
      }
    }
  }
//#pragma endscop
}