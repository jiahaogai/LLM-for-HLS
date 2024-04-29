Code: #pragma ACCEL kernel

void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 336; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 336; j++) {
      s = 0.0;
      
#pragma ACCEL PARALLEL reduction=s FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        idx = i * 336 + j + (-1 + k);
        if (idx < 0) {
          idx = 0;
        }
        if (idx > 8191) {
          idx = 8191;
        }
        s += ((double )filter[k]) * orig[idx];
      }
      sol[i * 336 + j] = s;
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 336; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 336; j++) {
      s = 0.0;
      
#pragma ACCEL PARALLEL reduction=s FACTOR=auto{16}
      for (k = 0; k < 9; k++) {
        idx = i * 336 + j + (-1 + k);
        if (idx < 0) {
          idx = 0;
        }
        if (idx > 8191) {
          idx = 8191;
        }
        s += ((double )filter[k]) * orig[idx];
      }
      sol[i * 336 + j] = s;
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 336; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 336; j++) {
      s = 0.0;
      
#pragma ACCEL PARALLEL reduction=s FACTOR=auto{8}
      for (k = 0; k < 9; k++) {
        idx = i * 336 + j + (-1 + k);
        if (idx < 0) {
          idx = 0;
        }
        if (idx > 8191) {
          idx = 8191;
        }
        s += ((double )filter[k]) * orig[idx];
      }
      sol[i * 336