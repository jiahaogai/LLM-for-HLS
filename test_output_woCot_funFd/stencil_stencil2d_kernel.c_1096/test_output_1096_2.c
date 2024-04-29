#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int r;
  int q;
  int p;
  int k1;
  int k2;
  int j;
  int i;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 64; j++) {
      sol[i * 64 + j] = ((double )0);
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (k2 = 0; k2 < 9; k2++) {
        k1 = k2 + 1 - 4;
        q = k1 > 0 ? 0 : -k1;
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        while (q <= 4 - 1) {
          p = q + 1 - 4;
          r = p > 0 ? 0 : -p;
          
#pragma ACCEL PIPELINE auto{off}
          
#pragma ACCEL TILE FACTOR=auto{1}
          
#pragma ACCEL PARALLEL FACTOR=auto{1}
          for (k1 = k2 + 4 - r; k1 < 4 + k2 - r; k1++) {
            for (k2 = k2 + 4 - q; k2 < 4 + k2 - q; k2++) {
              if (((i + r) >= 0) && ((i + r) < 64) && ((j + q) >= 0) && ((j + q) < 64)) {
                sol[i * 64 + j] += filter[k1 * 9 + k2] * orig[(i + r) * 64 + j + q];
              }
            }
          }
          q++;
        }
      }
    }
  }
//#pragma endscop
}