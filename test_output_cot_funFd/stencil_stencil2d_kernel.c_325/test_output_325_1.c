#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8192; j++) {
      tmp = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = -4; k < 5; k++) {
        k_col = i + k;
        if (k_col < 0) {
          k_col = 0;
        }
         else if (k_col > 8191) {
          k_col = 8191;
        }
        i_col = j + k;
        if (i_col < 0) {
          i_col = 0;
        }
         else if (i_col > 8191) {
          i_col = 8191;
        }
        tmp += filter[k + 4] * orig[k_col * 8192 + i_col];
      }
      sol[i * 8192 + j] = tmp;
    }
  }
}