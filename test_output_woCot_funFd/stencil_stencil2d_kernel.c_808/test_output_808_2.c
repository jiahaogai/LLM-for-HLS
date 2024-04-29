Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center;
  int flatten_idx;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{31}
  outer:
  for (i = 0; i < 128 + 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 64 + 8; j++) {
      center = orig[i * 128 + j];
      flatten_idx = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      inner:
      for (k = 0; k < 5; k++) {
        idx = range_assert(i * 128 + j * 8 + k - 4, 0, 8191);
        flatten_idx += filter[k] * orig[idx];
      }
      sol[i * 128 + j] = flatten_idx;
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
  int idx;
  int center;
  int flatten_idx;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{31}
  outer:
  for (i = 0; i < 128 + 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 64 + 8; j++) {
      center = orig[i * 128 + j];
      flatten_idx = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      inner:
      for (k = 0; k < 5; k++) {
        idx = range_assert(i * 128 + j * 8 + k - 4, 0, 8191);
        flatten_idx += filter[k] * orig[idx];
      }
      sol[i * 128 + j] = flatten_idx;
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
  int idx;
  int center;
  int flatten_idx;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{31}
  outer:
  for (i = 0; i < 128 + 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j <