#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double mult;
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{12}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{__PARA__L1}
      for (j = 0; j < 80; j++) {
        double temp1 = 0.0;
        double temp2 = 0.0;
        
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{__PARA__L3}
        for (long long _in_k = 0LL; _in_k < 60LL; _in_k++) {
          long long k;
          k = _in_k;
          mult = A[i][k] * B[k][j];
          temp1 += mult;
          temp2 += mult * A[i][k];
        }
	C[i][j] += temp1;
	A[i][j] = temp2;
      }
    }
  }
  
#pragma endscop
}