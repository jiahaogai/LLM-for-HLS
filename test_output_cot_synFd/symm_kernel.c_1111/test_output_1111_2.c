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
    
#pragma ACCEL PARALLEL FACTOR=auto{10}
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
        int _in_j = 0;
        int _in_k = 0;
        _in_j = j;
        _in_k = k;
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{2}
	for (int _in_kidx = 0; _in_kidx < 60; _in_kidx++) {
          int _in_k = _in_k + 1;
          temp2 += A[i][_in_k] * B[_in_k][_in_j];
        }
	C[i][j] += temp2;
      }
    }
  }
//#pragma endscop
}