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
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 1; i < 8191; i++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{9}
      loopk:
      for (k = 0; k < 9; k++) {
        i_col = i - 4 + k;
        if (((i_col >= 0) && (i_col < 8192))) {
          k_col = k - 4;
          if (((k_col >= 0) && (k_col < 9))) {
            sum += filter[k] * orig[i_col] * orig[k_col];
          }
        }
      }
      sol[j * 8192 + i] = sum;
    }
  }
}