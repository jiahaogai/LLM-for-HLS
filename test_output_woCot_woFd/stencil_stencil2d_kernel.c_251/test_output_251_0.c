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
  int t_col;
  
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
      inner:
      for (k = -4; k < 5; k++) {
        i_col = i + k;
        if (((i_col >= 0) && (i_col < 256))) {
          j_col = j - 4;
          outer_col:
          while (1) {
            if (((j_col >= 0) && (j_col < 256))) {
              t_col = i_col * 256 + j_col;
              t += filter[k + 4] * orig[t_col];
              j_col++;
            }
            else {
              break;
            }
          }
        }
      }
      sol[i * 256 + j] = t;
    }
  }
}