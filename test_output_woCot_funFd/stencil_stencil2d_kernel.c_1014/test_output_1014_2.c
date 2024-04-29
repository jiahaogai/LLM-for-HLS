However, it is not always practical to include a complete description of the function in the source code. In such cases, it is necessary to provide the function's implementation as a separate header file.

The following is the implementation of the function `stencil` that we included in a separate file, `stencil.c`, for demonstration purposes.

#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pt = 4;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        int orig_idx = (i + pt - 1) * 256 + (j + pt - 1) * 4 + k - 4;
        t += orig[orig_idx] * filter[k];
      }
      sol[i * 256 + j] = t;
    }
  }
}