#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int r;
  int c;
  int i;
  int j;
  int bound;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (r = 1; r < 8191; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (c = 1; c < 8191; c++) {
      sum = 0.0;
      bound = 8191 << 3;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (i = r - 4; i <= r + 4; i++) {
        
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
        for (j = c - 4; j <= c + 4; j++) {
          sum += filter[((i - (r - 4)) << 3) + (j - (c - 4)) ] * orig[i * 8192 + j];
        }
      }
      sol[r * 8192 + c] = sum;
    }
  }
}