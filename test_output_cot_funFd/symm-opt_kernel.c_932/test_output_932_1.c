Code: #pragma ACCEL PIPELINE auto{}
Error: 
__PIPE__L1: PIPELINE {flush}
__PIPE__L1: ACCEL PIPELINE {flush}
Code: #pragma ACCEL TILE FACTOR=auto{2}
Error: 
__TILE__L1: TILE FACTOR=auto{2}
__PIPE__L1: PIPELINE {off}
__PIPE__L1: ACCEL PIPELINE {off}
__TILE__L1: ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{12}
Error: 
__PARA__L1: PARALLEL FACTOR=auto{12}
__PIPE__L1: PIPELINE {off}
__PIPE__L1: ACCEL PIPELINE {off}
__TILE__L1: ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PIPELINE auto{}
Error: 
__PIPE__L2: PIPELINE {off}
__PIPE__L2: ACCEL PIPELINE {off}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Error: 
__TILE__L2: TILE FACTOR=auto{1}
__PIPE__L2: PIPELINE {off}
__PIPE__L2: ACCEL PIPELINE {off}
__TILE__L2: ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{32}
Error: 
__PARA__L2: PARALLEL FACTOR=auto{32}
__PIPE__L2: PIPELINE {off}
__PIPE__L2: ACCEL PIPELINE {off}
__TILE__L2: ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PIPELINE auto{}
Error: 
__PIPE__L3: PIPELINE {off}
__PIPE__L3: ACCEL PIPELINE {off}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Error: 
__TILE__L3: TILE FACTOR=auto{1}
__PIPE__L3: PIPELINE {off}
__PIPE__L3: ACCEL PIPELINE {off}
__TILE__L3: ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{4}
Error: 
__PARA__L3: PARALLEL FACTOR=auto{4}
__PIPE__L3: PIPELINE {off}
__PIPE__L3: ACCEL PIPELINE {off}
__TILE__L3: ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{__PARA__L3}
Error: 
__PARA__L3: PARALLEL reduction=temp2 FACTOR=auto{4}
__PIPE__L3: PIPELINE {off}
__PIPE__L3: ACCEL PIPELINE {off}
__TILE__L3: ACCEL TILE FACTOR=auto{1}
Code: 
#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{12}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE