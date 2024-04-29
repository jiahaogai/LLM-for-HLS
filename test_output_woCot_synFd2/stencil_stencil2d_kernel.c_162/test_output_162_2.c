#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[256])
{
  int i;
  int j;
  int k;
  int k_col;
  int flush;
  int off;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    sol[i] = ((int )0);
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      off = i - 4 + j;
      if (off < 0) {
        off += 8;
      }
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{8}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 0; k < 8; k++) {
        k_col = off + 4 + k;
        if (k_col >= 8192) {
          k_col -= 8192;
        }
        sol[i] += ((filter[k]) * orig[k_col]);
      }
    }
  }
}