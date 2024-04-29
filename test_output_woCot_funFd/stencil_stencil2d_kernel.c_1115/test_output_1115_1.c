Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    middle:
    for (j = 0; j < 64; j++) {
      inner:
      for (k = 0; k < 9; k++) {
        if (((i - 4 + k) < 0) || ((i - 4 + k) > 8191)) {
          result = 0;
        }
         else {
          result = orig[i - 4 + k];
        }
        sol[i] = result + filter[k] * sol[i];
      }
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
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 64; j++) {
      inner:
      for (k = 0; k < 9; k++) {
        if (((i - 4 + k) < 0) || ((i - 4 + k) > 8191)) {
          result = 0;
        }
         else {
          result = orig[i - 4 + k];
        }
        sol[i] = result + filter[k] * sol[i];
      }
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
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    middle:
    for (j = 0; j < 64; j++) {
      inner:
      for (k = 0; k < 9; k++) {
        if (((i - 4 + k) < 0) || ((i - 4 + k) > 8191)) {
          result = 0;
        }
         else {
          result = orig[i - 4 + k];
        }
        sol[i] = result + filter[k] * sol[i];
      }
    }
  }
}
Error: