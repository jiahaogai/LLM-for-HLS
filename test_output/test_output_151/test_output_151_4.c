
 
#pragma ACCEL kernel

void kernel_seidel_2d(int tsteps,int n,double A[90][90])
{
  int t;
  int i;
  int j;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t <= 39; t++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (i = 1; i <= 89; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      for (j = 1; j <= 89; j++) {
        A[i][j] = (double )0;
        for (q = 1; q <= 9; q++) {
          A[i][j] += _in_[(i + ((q - 1) * 1))][j] * _out[q];
        }
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
    for (i = 1; i <= 89; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      for (j = 1; j <= 89; j++) {
        _in_[i][j] = A[i][j];
      }
    }
  }
//#pragma endscop
}
