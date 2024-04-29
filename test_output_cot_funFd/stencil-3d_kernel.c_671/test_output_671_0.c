#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long t;
  long pt[32];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 1; i < 39303; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 1; j < 393; j++) {
      for (k = 1; k < 393; k++) {
        t = 27L * orig[((i - 1) * 393 + (j - 1)) * 393 + (k - 1)] + 
          orig[((i - 1) * 393 + j) * 393 + (k - 1)] + 
          orig[((i - 1) * 393 + (j + 1)) * 393 + (k - 1)] + 
          orig[(i * 393 + (j - 1)) * 393 + (k - 1)] + 
          orig[(i * 393 + (j + 1)) * 393 + (k - 1)] + 
          orig[((i + 1) * 393 + (j - 1)) * 393 + (k - 1)] + 
          orig[((i + 1) * 393 + j) * 393 + (k - 1)] + 
          orig[((i + 1) * 393 + (j + 1)) * 393 + (k - 1)] + 
          orig[(i * 393 + (k - 1)) * 393 + (j - 1)] + 
          orig[(i * 393 + (k - 1)) * 393 + j] + 
          orig[(i * 393 + (k - 1)) * 393 + (j + 1)] + 
          orig[(i * 393 + (k + 1)) * 393 + (j - 1)] + 
          orig[(i * 393 + (k + 1)) * 393 + j] + 
          orig[(i * 393 + (k + 1)) * 393 + (j + 1)];
        sol[(i * 393 + j) * 393 + k] = ((t + 16L) / 64L);
      }
    }
  }
}