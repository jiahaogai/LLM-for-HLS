Code: #pragma ACCEL PIPELINE auto{}
Error: 
__PIPE__ 0
Code: #pragma ACCEL TILE FACTOR=auto{2}
Error: 
__TILE__ __FACTOR__ 2
Code: #pragma ACCEL PARALLEL FACTOR=auto{12}
Error: 
__PARA__L1 __FACTOR__ 12
Code: #pragma ACCEL PIPELINE auto{}
Error: 
__PIPE__ 1
Code: #pragma ACCEL TILE FACTOR=auto{1}
Error: 
__TILE__ 
Code: #pragma ACCEL PARALLEL FACTOR=auto{32}
Error: 
__PARA__L2 __FACTOR__ 32
Code: #pragma ACCEL PIPELINE auto{}
Error: 
__PIPE__ 2
Code: #pragma ACCEL TILE FACTOR=auto{1}
Error: 
__TILE__ 
Code: #pragma ACCEL PARALLEL FACTOR=auto{4}
Error: 
__PARA__L3 __FACTOR__ 4
Code: #pragma ACCEL PIPELINE auto{off}
Error: 
__PIPE__ 3
Code: #pragma ACCEL TILE FACTOR=auto{1}
Error: 
__TILE__ 
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Error: 
__PARA__L4 __FACTOR__ 1
Code: 
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{__PARA__L3}
      for (j = 0; j < 80; j++) {
        temp2 = 0.0;
        
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{8}
        for (m = 0; m < 60; m++) {
          temp2 += A[i][m] * B[m][j];
        }
        C[i][j] += temp1 * temp2;
      }
    }
  }
}