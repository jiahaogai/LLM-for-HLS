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
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    middle:
    for (j = 0; j < 8192; j++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{62}
      inner:
      for (k = -4; k < 5; k++) {
        k_col = k + i;
        i_col = j + k;
        if ((((i_col >= 0) && (i_col < 8192)) && ((k_col >= 0) && (k_col < 8192))) && smoothing_allowed(i_col, k_col)) {
          sum += filter[((unsigned int )k) + 4] * orig[i_col];
        }
      }
      sol[j] = sum;
    }
  }
}