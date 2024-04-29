#pragma ACCEL kernel

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
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{5}
    for (j = 0; j < 240; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 200; k++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{8}
      for (j = 0; j < 240; j++) {
        double temp2 = 0.0;
        
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{8}
        for (j = 0; j < 200; j++) {
          temp2 += A[i][j] * B[j][k];
        }
	C[i][k] += alpha * temp2;
      }
    }
  }
//#pragma endscop
}