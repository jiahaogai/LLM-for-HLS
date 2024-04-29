Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
  int idx = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 32; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 32; j++) {
      inner:
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[idx + ((-1 + k) << 32)];
      }
      sol[idx] = result;
      result = 0;
      idx++;
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
  int idx = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 1; i < 256 + 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 1; j < 256 + 1; j++) {
      inner:
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[idx + ((-1 + k) << 32)];
      }
      sol[idx] = result;
      result = 0;
      idx++;
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
  int idx = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 8; i < 256 + 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 8; j < 256 + 8; j++) {
      inner:
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[idx + ((-1 + k) << 32)];
      }
      sol[idx] = result;
      result = 0;
      idx++;
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
  int idx = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 1; i < 256 + 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle