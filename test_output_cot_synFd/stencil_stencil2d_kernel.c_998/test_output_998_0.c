#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int r;
  int c;
  int i;
  int j;
  int k1;
  int k2;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (r = 1; r < 8191; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (c = 1; c < 8191; c++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (j = -1; j <= 1; j++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{2}
        for (i = -1; i <= 1; i++) {
          k1 = r + i;
          k2 = c + j;
          sum += filter[((i + 1) * 3) + (j + 1)] * orig[k1 * 8192 + k2];
        }
      }
      sol[r * 8192 + c] = sum;
    }
  }
}