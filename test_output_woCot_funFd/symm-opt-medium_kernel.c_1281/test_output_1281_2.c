Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[200][240],double A[200][200],double B[200][240])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{4}
    for (j = 0; j < 240; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (k = 0; k < 200; k++) {
      
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{8}
      for (j = 0; j < 240; j++) {
        double temp1 = 0.0;
        double A_elem = A[i][k];
        for (long long _in_j = 0; _in_j < 200; _in_j++) {
          double B_elem = B[k][_in_j];
          temp1 += A_elem * B_elem;
        }
        temp1 = alpha * temp1;
        C[i][j] += temp1;
      }
    }
  }
//#pragma endscop
}