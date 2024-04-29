Code: #pragma ACCEL TILE FACTOR=auto{1}`: Keep the loop `stencil_label3` whole, without dividing it into smaller parts.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations of the loop `stencil_label3` sequentially, not concurrently.


#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      sum = 0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
      inner:
      for (k = -4; k < 5; k++) {
        idx = (256 * (i + 4)) + (j + k);
        if (idx < 0) {
          idx = 0;
        }
         else {
          if (idx > 8191) {
            idx = 8191;
          }
        }
        sum += orig[idx] * filter[k + 4];
      }
      sol[i * 256 + j] = sum;
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{1}`: Keep the loop `stencil_label3` whole, without dividing it into smaller parts.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations of the loop `stencil_label3` sequentially, not concurrently.


#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      sum = 0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
      inner:
      for (k = -4; k < 5; k++) {
        idx = (256 * (i + 4)) + (j + k);
        if (idx < 0) {
          idx = 0;
        }
         else {
          if (idx > 8191) {
            idx = 8191;
          }
        }
        sum += orig[idx] * filter[k + 4];
      }
      sol[i * 256 + j] = sum;
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{1}`: Keep the loop `stencil_label3` whole, without dividing it into smaller parts.
- `#pragma ACCEL PARAL