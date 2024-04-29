Summary: 
 
#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (k = 0; k < 40; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{8}
    for (j = 0; j < 40; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (i = 0; i < 40; i++) {
        sol[index(i,j,k)] = ((C0*orig[index(i - 1,j,k)]) + (C1*orig[index(i + 1,j,k)])) + ((C0*orig[index(i,j - 1,k)]) + (C1*orig[index(i,j + 1,k)])) + ((C0*orig[index(i,j,k - 1)]) + (C1*orig[index(i,j,k + 1)])) ;
      }
    }
  }
//#pragma endscop
}