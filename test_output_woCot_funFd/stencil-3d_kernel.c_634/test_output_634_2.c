#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long tid;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
  for (j = 1; j < 32 + 1; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{3}
    loopk_col:
    for (k_col = 1; k_col < 32 + 1; k_col++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{32}
      loopk:
      for (k = 0; k < 30 + 1; k++) {
        i_col = k_col - 1 + (30 + 1) * (k - 1);
        tid = i_col;
        sum += orig[tid] / 32.0;
      }
      sol[i_col] = sum;
    }
  }
}