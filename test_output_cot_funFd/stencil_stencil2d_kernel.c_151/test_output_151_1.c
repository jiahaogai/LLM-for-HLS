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
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    sum = 0.0;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    inner:
    for (j = 0; j < 9; j++) {
      k_col = ((i - 4) + j) < 0 ? 0 : ((i - 4) + j) > 8191 ? 8191 : ((i - 4) + j);
      i_col = i < 4 ? 0 : i > 8191 ? 8191 : i;
      sum += filter[j] * orig[k_col] + sol[i_col];
    }
    sol[i] = sum;
  }
}