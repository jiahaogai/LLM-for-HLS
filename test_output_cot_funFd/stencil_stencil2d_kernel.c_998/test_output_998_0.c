#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8192; j++) {
      sol[i * 8192 + j] = 0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((8192 + 9 - 1) - k) % 9;
        i_col = (i - 4) + k_col;
        if (i_col < 0) {
          i_col += 8192;
        }
        else {
          if (i_col > 8191) {
            i_col -= 8192;
          }
        }
        j_col = (j - 4) + k_col;
        if (j_col < 0) {
          j_col += 8192;
        }
        else {
          if (j_col > 8191) {
            j_col -= 8192;
          }
        }
        sol[i * 8192 + j] += filter[k] * orig[i_col * 8192 + j_col];
      }
    }
  }
}