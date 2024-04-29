#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int r;
  int q;
  int p;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  for (r = 0; r < 8; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 8; q++) {
      double sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{7}
      for (p = 0; p < 8; p++) {
        int i = r * 8 + p;
        int j = q * 8;
        sum += filter[p] * orig[i * 64 + j];
      }
      sol[r * 8 + q] = sum;
    }
  }
//#pragma endscop
}