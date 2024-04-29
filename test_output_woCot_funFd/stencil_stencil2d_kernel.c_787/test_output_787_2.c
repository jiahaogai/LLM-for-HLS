#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    i_col = i % 64;
    middle:
    for (j = 0; j < 8192; j++) {
      k_col = j % 64;
      mult = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        mult += filter[k] * orig[i + ((-4 + k) % 8) * 64 + k_col];
      }
      sol[i * 8192 + j] = mult;
    }
  }
}