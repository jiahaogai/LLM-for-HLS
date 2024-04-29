#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int r;
  int q;
  int p;
  int k1;
  int k2;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  outer:
  for (r = 0; r < 8; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (q = 0; q < 8; q++) {
      sum = 0.0;
      inner:
      for (p = 0; p < 9; p++) {
        k1 = r + ((p + 1) / 3 - 1);
        k2 = q + ((p + 1) % 3 - 1);
        if ((k1 >= 0) && (k1 < 8) && (k2 >= 0) && (k2 < 8)) {
          sum += filter[p] * orig[k1 * 8 + k2];
        }
      }
      sol[r * 8 + q] = sum;
    }
  }
}