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
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{32}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = i - 4 + k;
        if (k_col < 0 || k_col > 8191) {
          k_col = 0;
        }
        i_col = j - 4 + k;
        if (i_col < 0 || i_col > 8191) {
          i_col = 0;
        }
        sum += filter[k] * orig[k_col * 8192 + i_col];
      }
      sol[i * 8192 + j] = sum;
    }
  }
}