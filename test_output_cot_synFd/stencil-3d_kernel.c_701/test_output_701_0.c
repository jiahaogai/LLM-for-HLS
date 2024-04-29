#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[27],long sol[27])
{
  long i;
  long j;
  long k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  for (k = 0; k < 16; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 16; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (i = 0; i < 16; i++) {
        sol[k * 16 * 16 + j * 16 + i] = ((C0 * orig[k * 16 * 16 + j * 16 + i]) + (C1 * (orig[k * 16 * 16 + j * 16 + i + 16] + orig[k * 16 * 16 + j * 16 + i - 16] + orig[k * 16 * 16 + (j + 1) * 16 + i] + orig[k * 16 * 16 + (j - 1) * 16 + i] + orig[(k + 1) * 16 * 16 + j * 16 + i] + orig[(k - 1) * 16 * 16 + j * 16 + i]))) / 4.0;
      }
    }
  }
//#pragma endscop
}