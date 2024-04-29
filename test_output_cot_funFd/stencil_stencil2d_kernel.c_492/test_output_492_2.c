Code: ### ACCEL kernel: 

#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_up;
  int col_down;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
/* Standardize from: for(j = 1; j < 33 - 1; j++) {...} */
  for (j = 1 + 8; j < 32 + 8 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
/* Standardize from: for(i = 1; i < 33 - 1; i++) {...} */
    for (i = 1 + 8; i < 32 + 8 - 1; i++) {
      t = 0;
      row_up = 8 * (j - 1);
      row_down = 8 * (j + 1 - 1);
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      loopk:
      for (k = 1 + 8; k < 32 + 8 - 1; k++) {
        col_up = 8 * (k - 1);
        col_down = 8 * (k + 1 - 1);
        row = row_up + k - 8;
        col = col_up + i - 8;
        t += orig[row * 64 + col] * filter[k - 4];
      }
      sol[j * 64 + i] = t;
    }
  }
}