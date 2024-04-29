- `#pragma ACCEL PARALLEL FACTOR=auto{16}`: Divide the loop into parallelize it into 16 separate instances to exploit parallelism.

#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int t;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((k + i) < 256 ? (k + i) : (k + i - 256));
        i_col = ((i + 1) < 256 ? (i + 1) : (i + 1 - 256));
        j_col = ((j + 1) < 256 ? (j + 1) : (j + 1 - 256));
        t += filter[k] * orig[i_col * 256 + j_col] * orig[k_col * 256 + j_col];
      }
      sol[i * 256 + j] = t;
    }
  }
}