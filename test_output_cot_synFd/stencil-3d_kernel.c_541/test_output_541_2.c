#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{4}

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long k_col;
  long j_col;
  long i_col;
  long upper_bound;
  long lower_bound;
  long t1;
  long t2;
  long t3;
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopk:
  for (k = 1; k < 32 + 1; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
    for (j = 1; j < 32 + 1; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
      for (i = 1; i < 32 + 1; i++) {
        idx = ((((k - 1) * (32 + 1) + (j - 1)) * (32 + 1) + (i - 1)) * 2);
        k_col = ((((k - 1) * (32 + 1) + (j - 1)) * (32 + 1) + (i - 1)) * 2 + 1);
        j_col = (((k - 1) * (32 + 1) + (j - 1)) * 2 + 1);
        i_col = ((k - 1) * 2 + 1);
        t1 = orig[k_col - 1] + orig[k_col + 1] + orig[j_col - 1] + orig[j_col + 1] + orig[i_col - 1] + orig[i_col + 1] - 4 * orig[idx];
        t2 = orig[k_col - 1 + 32 * (1 + 32)] + orig[k_col + 1 + 32 * (1 + 32)] + orig[j_col - 1 + 32 * (1 + 1)] + orig[j_col + 1 + 32 * (1 + 1)] + orig[i_col - 1] + orig[i_col + 1] - 4 * orig[idx + 1];
        t3 = t1 + t2;
        sol[idx] = t3;
        upper_bound = 140;
        lower_bound = 120;
        if (t3 < lower_bound) {
          sol[idx] = lower_bound;
        }
        if (t3 > upper_bound) {
          sol[idx] = upper_bound;
        }
      }
    }
  }
}