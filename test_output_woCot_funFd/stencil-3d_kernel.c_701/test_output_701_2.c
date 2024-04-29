#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[27],long sol[27])
{
  long i;
  long j;
  long k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  for (k = 1; k < 27 - 1; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 1; j < 27 - 1; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (i = 1; i < 27 - 1; i++) {
        sol[k * 27 + j * 3 + i] = ((C1 * (orig[k * 27 + j * 3 + i + 1] - 2.0 * orig[k * 27 + j * 3 + i] + orig[k * 27 + j * 3 + i - 1])) / (C0 * C0) + (C0 * (orig[k * 27 + j * 3 + i + 27] - 2.0 * orig[k * 27 + j * 3 + i + 1] + orig[k * 27 + j * 3 + i]))) / (C0 * (27.0 - 2.0)) - 1.0;
      }
    }
  }
//#pragma endscop
}