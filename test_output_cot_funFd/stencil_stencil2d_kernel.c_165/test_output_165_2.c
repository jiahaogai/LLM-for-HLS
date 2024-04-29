#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    middle:
    for (j = 0; j < 8192; j++) {
      mult = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{62}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((8192 == 1) ? 0 : 1) + ((8192 - 2) * (k % 8));
        k_row = ((8 == 1) ? 0 : 1) + ((8 - 2) * (k / 8));
        mult += filter[k] * orig[i + k_row - 1] [j + k_col - 1];
      }
      sol[i] [j] = mult;
    }
  }
}