#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long tmp;
  long C0_idx;
  long C1_idx;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopj(32) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk(32) {
      loopi(32) {
        idx = i + 32L * (j + 32L * k);
        C0_idx = C0 + 390624L * k;
        C1_idx = C1 + 390624L * k;
        tmp = ((orig[C0_idx + 32L * j + i] + orig[C0_idx + 32L * (j - 1L) + i]) + orig[C0_idx + 32L * (j + 1L) + i]) + (orig[C0_idx + 32L * j + i - 1L] + orig[C0_idx + 32L * j + i + 1L]) + orig[C0_idx + 32L * (j - 1L) + i - 1L] + orig[C0_idx + 32L * (j - 1L) + i + 1L] + orig[C0_idx + 32L * (j + 1L) + i - 1L] + orig[C0_idx + 32L * (j + 1L) + i + 1L] + orig[C1_idx + 32L * j + i];
        sol[idx] = tmp;
      }
    }
  }
}