Code: d
 #pragma ACCEL kernel

void stencil3d(long C0,long C1,long C2,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  for (k = 0; k < 40; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 40; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (i = 0; i < 40; i++) {
        sol[index(i,j,k)] = ((2 * orig[index(i - 1,j - 1,k - 1)]) + (2 * orig[index(i - 1,j - 1,k)]) + (2 * orig[index(i - 1,j - 1,k + 1)]) + (2 * orig[index(i - 1,j,k - 1)]) + (5 * orig[index(i - 1,j,k)]) + (2 * orig[index(i - 1,j,k + 1)]) + (2 * orig[index(i - 1,j + 1,k - 1)]) + (2 * orig[index(i - 1,j + 1,k)]) + (2 * orig[index(i - 1,j + 1,k + 1)]) + (2 * orig[index(i,j - 1,k - 1)]) + (5 * orig[index(i,j - 1,k)]) + (2 * orig[index(i,j - 1,k + 1)]) + (2 * orig[index(i,j,k - 1)]) + (10 * orig[index(i,j,k)]) + (2 * orig[index(i,j,k + 1)]) + (2 * orig[index(i,j + 1,k - 1)]) + (2 * orig[index(i,j + 1,k)]) + (2 * orig[index(i,j + 1,k + 1)]) + (2 * orig[index(i + 1,j - 1,k - 1)]) + (2 * orig[index(i + 1,j - 1,k)]) + (2 * orig[index(i + 1,j - 1,k + 1)]) + (2 * orig[index(i + 1,j,k - 1)]) + (5 * orig[index(i + 1,j,k)]) + (2 * orig[index(i + 1,j,k + 1)]) + (2 * orig[index(i + 1,j + 1,k - 1)]) + (2 * orig[index(i + 1,j + 1,k)]) + (2 * orig[index(i + 1,j + 1,k + 1)])) / 80;
      }
    }
  }
//#pragma endscop
}