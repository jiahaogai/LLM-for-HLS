- `#pragma ACCEL PARALLEL FACTOR=auto{8}`: Divide the loop into partitions of 8 to exploit parallelism.

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
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{8}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((8 * i) + (k / 8));
        i_col = ((k % 8) + 1);
        j_col = ((8 * j) + (i_col - 1));
        t += ((filter[k]) * orig[j_col * 256 + k_col]);
      }
      sol[j * 256 + i] = t;
    }
  }
}