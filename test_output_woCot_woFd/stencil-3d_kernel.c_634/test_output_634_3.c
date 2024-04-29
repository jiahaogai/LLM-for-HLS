#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{2}
void kernel_stencil(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (i = 1; i < 32 + 1; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (j = 1; j < 32 + 1; j++) {
      for (k = 1; k < 32 + 1; k++) {
        sol[index(i, j, k)] = ((C0 * orig[index(i, j, k)]) + (C1 * (orig[index(i - 1, j, k)] + orig[index(i + 1, j, k)] + orig[index(i, j - 1, k)] + orig[index(i, j + 1, k)] + orig[index(i, j, k - 1)] + orig[index(i, j, k + 1)]))) / (C0 + C1);
      }
    }
  }
//#pragma endscop
}