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
    
#pragma ACCEL PARALLEL reduction = C FACTOR=auto{8}
    for (j = 0; j < 240; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 200; k++) {
      
#pragma ACCEL PARALLEL reduction = temp2 FACTOR=auto{10}
      for (j = 0; j < 240; j++) {
        double temp2 = 0.0;
        double A_elem = A[i][k];
        
#pragma ACCEL PARALLEL reduction = temp2 FACTOR=auto{1}
        for (int _in_A = 0; _in_A < 200; _in_A++) {
          double B_elem = B[_in_A][j];
          temp2 += A_elem * B_elem;
        }
        temp2 = alpha * temp2;
        C[i][j] += temp2;
      }
    }
  }
//#pragma endscop
}