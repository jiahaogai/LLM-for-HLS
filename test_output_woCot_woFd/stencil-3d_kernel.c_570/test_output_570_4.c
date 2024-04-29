#pragma ACCEL kernel

void stencil3d(long C0,long C1,long C2,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  for (i = 0; i < 32; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 32; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (k = 0; k < 32; k++) {
        sol[i * 32 + j * 32 + k] = ((orig[i * 32 + j * 32 + k] + orig[i * 32 + j * 32 + (k + 1)] + orig[i * 32 + (j + 1) * 32 + k] + orig[i * 32 + (j + 1) * 32 + (k + 1)] + orig[(i + 1) * 32 + j * 32 + k] + orig[(i + 1) * 32 + j * 32 + (k + 1)] + orig[(i + 1) * 32 + (j + 1) * 32 + k] + orig[(i + 1) * 32 + (j + 1) * 32 + (k + 1)]) / 8);
      }
    }
  }
//#pragma endscop
}