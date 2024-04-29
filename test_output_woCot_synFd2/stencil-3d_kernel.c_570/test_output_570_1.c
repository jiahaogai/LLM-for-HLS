#pragma ACCEL kernel

void stencil3d(long C0,long C1,long C2,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long s;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loopj:
  for (j = 1; j < 32 + 1; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
    for (k = 1; k < 32 + 1; k++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
      for (i = 1; i < 32 + 1; i++) {
        idx = i + ((j - 1) * (32 + 1)) + ((k - 1) * (32 + 1) * (32 + 1));
        s = orig[idx] + ((j > 1 ? orig[idx - 1] : 0) + (j < 32 ? orig[idx + 1] : 0) + (k > 1 ? orig[idx - (32 + 1)] : 0) + (k < 32 ? orig[idx + (32 + 1)] : 0) + (((32 + 1) * (32 + 1)) > ((k - 1) * (32 + 1)) ? orig[idx - ((32 + 1) * (32 + 1))] : 0) + (((32 + 1) * (32 + 1)) > (32 * (k - 1)) ? orig[idx - ((32 + 1) * (k - 1))] : 0)) - (((32 + 1) * (32 + 1)) > (32 * (k + 1)) ? orig[idx + ((32 + 1) * (k + 1))] : 0) - (((32 + 1) * (32 + 1)) > ((k + 1) * (32 + 1)) ? orig[idx + ((32 + 1) * (32 + 1)) - 1] : 0);
        sol[idx] = s;
      }
    }
  }
}