#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int r;
  int c;
  int i;
  int j;
  int bound;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (r = 1; r < 8191; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (c = 1; c < 8191; c++) {
      bound = 8192 + 1;
      sol[r * 8192 + c] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (i = r - 4; i <= r + 4; i++) {
        
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{16}
        for (j = c - 4; j <= c + 4; j++) {
          if (((i < 0) || (i > 8191)) || ((j < 0) || (j > 8191))) {
            continue;
          }
          else {
            sol[r * 8192 + c] += filter[((i - r + 4) + 5) * 9 + ((j - c + 4) + 5)] * orig[i * 8192 + j];
          }
        }
      }
    }
  }
//#pragma endscop
}