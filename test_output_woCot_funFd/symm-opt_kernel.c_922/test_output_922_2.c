#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{12}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{__PARA__L3}
      for (j = 0; j < 80; j++) {
        double temp2 = 0.0;
        int _in_j;
        int _in_k;
        _in_j = 0;
        _in_k = 0;
        #pragma ACCEL PARAMS auto{j} auto{k}
        while (_in_j < 80) {
          #pragma ACCEL PARAMS auto{A} auto{_in_j} auto{k}
          double A_tmp = A[i][_in_j];
          #pragma ACCEL PARAMS auto{B} auto{k} auto{j}
          double B_tmp = B[k][j];
          temp2 += A_tmp * B_tmp;
          _in_j += 1;
          _in_k = 0;
        }
        C[i][j] += temp2;
      }
    }
  }
//#pragma endscop
}