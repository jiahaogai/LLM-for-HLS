**Optimize for:**
`{ "lookahead": "auto{off}", "pipeline": "auto{off}", "tile": "auto{off}", "parallel": "auto{off}", "relax": "auto{off}", "channels": [ "auto{intl}", "auto{intl}", "auto{intl}", "auto{intl}", "auto{intl}", "auto{intl}", "auto{intl}", "auto{intl}", "auto{intl}" ] }`

#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  int row;
  int col;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  loopj:
/* Standardize from: for(j ... ) */
  for (j = 2; j < 64 - 2; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk_col:
/* Standardize from: for(k_col ... ) */
    for (k_col = 2; k_col < 64 - 2; k_col++) {
      val = 0;
      
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{1}
      loopk_row:
/* Standardize from: for(k_row ... ) */
      for (k_row = 0; k_row < 3; k_row++) {
        
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{16}
        loopk:
/* Standardize from: for(k ... ) */
        for (k = 0; k < 3; k++) {
          i = k_row * 3 + k;
          row = j + (-1 + i);
          col = k_col + (-1 + k);
          val += orig[row * 64 + col] * filter[k];
        }
      }
      sol[j * 64 + k_col] = val;
    }
  }
}