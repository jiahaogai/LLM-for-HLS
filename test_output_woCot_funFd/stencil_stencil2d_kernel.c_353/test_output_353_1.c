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
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 8192; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{8}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((8192 + 8) + k) - 8192;
        i_col = i + k_col;
        if (i_col < 0) {
          i_col = 0;
        }
        if (i_col > 8191) {
          i_col = 8191;
        }
        j_col = j + k_col;
        if (j_col < 0) {
          j_col = 0;
        }
        if (j_col > 8191) {
          j_col = 8191;
        }
        t += ((orig[i_col * 8192 + j_col]) * (filter[k])) ;
      }
      sol[i * 8192 + j] = t;
    }
  }
}