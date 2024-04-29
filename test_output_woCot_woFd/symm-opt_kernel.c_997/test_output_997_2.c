#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double tmp;
  double mult;
  double _in_C_[60][80];
  double _in_A_[60][60];
  double _in_B_[60][80];
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      _in_C_[i][j] = C[i][j];
    }
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=_in_C_ FACTOR=auto{1}
      for (j = 0; j < 80; j++) {
        tmp = 0.0;
        
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
        for (jj = 0; jj < 60; jj++) {
          mult = A[i][jj] * B[jj][j];
          tmp += mult;
        }
        _in_C_[i][j] += tmp;
      }
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      C[i][j] = _in_C_[i][j];
    }
  }
}