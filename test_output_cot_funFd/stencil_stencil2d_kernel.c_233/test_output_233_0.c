#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int row;
  int col;
  int flr;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j ... ) */
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loopi:
/* Standardize from: for(i ... ) */
    for (i = 1; i < 32; i++) {
      idx = i + JA1 * j;
      row = i - 1 + JA1 * (j - 1);
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loopk:
/* Standardize from: for(k ... ) */
      for (k = 0; k < 9; k++) {
        col = row + KA[k];
        flr = col * 32 + idx;
        sol[flr] = filter[k] * orig[flr];
      }
    }
  }
}