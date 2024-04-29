Code: #pragma ACCEL kernel

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
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 64; j++) {
      i_col = i - 4;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 0; k < 4; k++) {
        if (i_col + k < 0) {
          k_col = 0;
        }
         else if (i_col + k > 8191) {
          k_col = 8191;
        }
         else {
          k_col = i_col + k;
        }
        j_col = j - 4;
        if (j_col < 0) {
          j_col = 0;
        }
         else if (j_col > 63) {
          j_col = 63;
        }
        t = 0;
        inner_1:
        for (k_filter = 0; k_filter < 9; k_filter++) {
          t += filter[k_filter] * orig[k_col * 64 + j_col + k_filter];
        }
        sol[i * 64 + j] = t;
      }
    }
  }
}