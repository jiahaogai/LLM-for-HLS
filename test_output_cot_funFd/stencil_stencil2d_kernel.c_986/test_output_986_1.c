#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flatten_row;
  int flatten_col;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loopj:
/* Standardize from: for(j ... ) */
  for (j = 0; j < 32; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k ... ) */
    for (k = 0; k < 32; k++) {
      i = j * 32 + k;
      flatten_row = j * 32;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopcol:
      for (col = 0; col < 32; col++) {
        flatten_col = col * 32;
        idx = flatten_row + flatten_col + k;
        val = 0;
        
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{32}
        loopfilter:
        for (row = 0; row < 9; row++) {
          val += orig[idx + row - 4] * filter[row];
        }
        sol[i] = val;
      }
    }
  }
}