#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long idx_n;
  long idx_s;
  long idx_w;
  long idx_e;
  long idx_nw;
  long idx_ne;
  long idx_sw;
  long idx_se;
  long tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopk:
  for (k = 2; k < 39300 - 2; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
    for (j = 2; j < 39300 - 2; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
      for (i = 2; i < 39300 - 2; i++) {
        k_col = k - 2;
        i_col = i - 2;
        idx = ((k_col * 39300) + i_col) * 2;
        idx_n = idx + 2 * 39300;
        idx_s = idx - 2 * 39300;
        idx_w = idx - 2;
        idx_e = idx + 2;
        idx_nw = idx_n - 2;
        idx_ne = idx_n - 1;
        idx_sw = idx_s - 2;
        idx_se = idx_s - 1;
        tmp = (orig[idx] + orig[idx_n] + orig[idx_s] + orig[idx_w] + orig[idx_e] + orig[idx_nw] + orig[idx_ne] + orig[idx_sw] + orig[idx_se]) / 9L;
        sol[idx] = tmp;
      }
    }
  }
}