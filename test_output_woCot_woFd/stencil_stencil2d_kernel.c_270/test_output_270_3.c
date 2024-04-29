#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 8192; j++) {
      sum = ((double )0);
      inner:
      for (k = -4; k < 5; k++) {
        k_col = i + k;
        if (k_col < 0) {
          k_col += 8192;
        }
        
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{32}
        i_col:
        for (j_col = -4; j_col < 5; j_col++) {
          int k_col_pad;
          int j_col_pad;
          if (k_col < 0) {
            k_col_pad = k_col + 8192;
          }
          else {
            if (k_col > 8191) {
              k_col_pad = k_col - 8192;
            }
            else {
              k_col_pad = k_col;
            }
          }
          
          if (j_col < 0) {
            j_col_pad = j_col + 8192;
          }
          else {
            if (j_col > 8191) {
              j_col_pad = j_col - 8192;
            }
            else {
              j_col_pad = j_col;
            }
          }
          sum += filter[k + 4] * orig[k_col_pad * 8192 + j_col_pad] ;
        }
      }
      sol[i * 8192 + j] = sum;
    }
  }
}