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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{32}
      inner:
      for (k = 0; k < 9; k++) {
        int k_col_int = k - 4;
        int i_col_int = i - 4;
        int j_col_int = j - 4;
        int k_col = ((k_col_int > 0) ? k_col_int : 0);
        int i_col = ((i_col_int > 0) ? i_col_int : 0);
        int j_col = ((j_col_int > 0) ? j_col_int : 0);
        int k_idx = k_col + 8 * i_col + 8192 * j_col;
        t += filter[k] * orig[k_idx];
      }
      sol[i + 8192 * j] = t;
    }
  }
}