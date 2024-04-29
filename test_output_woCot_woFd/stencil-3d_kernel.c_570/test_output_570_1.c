#pragma ACCEL kernel

void stencil3d(long C0,long C1,long C2,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  for (k = 0; k < 32; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 32; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (i = 0; i < 32; i++) {
        sol[index(i,j,k)] = ((orig[index(i - 1,j,k)] + orig[index(i + 1,j,k)]) + (orig[index(i,j - 1,k)] + orig[index(i,j + 1,k)])) + (orig[index(i,j,k - 1)] + orig[index(i,j,k + 1)]);
      }
    }
  }
//#pragma endscop
}