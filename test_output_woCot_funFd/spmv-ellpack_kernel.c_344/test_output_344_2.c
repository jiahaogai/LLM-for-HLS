Code: #pragma ACCEL kernel

void kernel_1(double in_1[250][250],double out_1[250][250])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  spmv_1:
  for (i = 0; i < 250; i++) {
    
#pragma ACCEL PARALLEL reduction = out_1 FACTOR=auto{8}
    spmv_2:
    for (j = 0; j < 250; j++) {
      out_1[i][j] += in_1[i][0] * in_1[0][j];
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_1(double in_1[250][250],double out_1[250][250])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  spmv_1:
  for (i = 0; i < 250; i++) {
    
#pragma ACCEL PARALLEL reduction = out_1 FACTOR=auto{8}
    spmv_2:
    for (j = 0; j < 250; j++) {
      out_1[i][j] += in_1[i][0] * in_1[0][j];
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_1(double in_1[250][250],double out_1[250][250])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  spmv_1:
  for (i = 0; i < 250; i++) {
    
#pragma ACCEL PARALLEL reduction = out_1 FACTOR=auto{8}
    spmv_2:
    for (j = 0; j < 250; j++) {
      out_1[i][j] += in_1[i][0] * in_1[0][j];
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_1(double in_1[250][250],double out_1[250][250])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  spmv_1:
  for (i = 0; i < 250; i++) {
    
#pragma ACCEL PARALLEL reduction = out_1 FACTOR=auto{8}
    spmv_2:
    for (j = 0; j < 250; j++) {
      out_1[i][j] += in_1[i][0] * in_1[0][j];
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_1(double in_1[250][250],double out_1[250][250])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma A