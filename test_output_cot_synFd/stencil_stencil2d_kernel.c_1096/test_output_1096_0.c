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
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 64; j++) {
      double sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{7}
      for (k2 = -4; k2 <= 4; k2++) {
        int k2_col = k2 * 64;
        
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
        for (k1 = -4; k1 <= 4; k1++) {
          int k1_idx = (k1 + 4) * 8;
          int k1_col = k1_idx * 64;
          sum += filter[k1 + 4] * orig[i * 64 + k1_idx + k2 + 4] ;
        }
      }
      sol[i * 64 + j] = sum;
    }
  }
//#pragma endscop
}