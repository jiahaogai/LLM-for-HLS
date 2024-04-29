#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 8192; j++) {
      mult = 0.0;
      
#pragma ACCEL PARALLEL reduction=mult FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((8192 + 1) * k) + i;
        i_col = ((8192 + 1) * k) + j;
        mult += filter[k] * orig[k_col] * orig[i_col];
      }
      sol[j] = mult;
    }
  }
}