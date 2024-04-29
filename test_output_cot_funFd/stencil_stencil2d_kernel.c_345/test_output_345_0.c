#pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{1}

void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flit;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_row:
/* Standardize from: for(row = 0; row < 32; row++) {...} */
  for (row = 0; row <= 31; row++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_col:
/* Standardize from: for(col = 0; col < 32; col++) {...} */
    for (col = 0; col <= 31; col++) {
      i = row * 32 + col;
      flit = orig[i];
      
#pragma ACCEL PARALLEL FACTOR=auto{32}
      loop_k:
      for (k = 0; k < 9; k++) {
        j = k - 4 + row * 32 + col;
        sol[i] += filter[k] * orig[j];
      }
    }
  }
}