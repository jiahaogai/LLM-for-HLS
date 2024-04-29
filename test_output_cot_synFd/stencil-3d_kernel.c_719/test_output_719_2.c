#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{2}

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long k_col;
  long j_col;
  long i_col;
  long km;
  long jm;
  long im;
  long kp;
  long jp;
  long ip;
  long tmp;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk_col:
/* Standardize from: for(k_col = 1;k_col < 40;k_col ++) {...} */
  for (k_col = 1; k_col < 40 + 1; k_col++) {
    long _in_k_col = 0 + 39L * (0 + 39L * (k_col - 1));
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj_col:
/* Standardize from: for(j_col = 1;j_col < 40;j_col ++) {...} */
    for (j_col = 1; j_col < 40 + 1; j_col++) {
      long _in_j_col = _in_k_col + 39L * (j_col - 1);
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi_col:
/* Standardize from: for(i_col = 1;i_col < 40;i_col ++) {...} */
      for (i_col = 1; i_col < 40 + 1; i_col++) {
        long _in_i_col = _in_j_col + i_col - 1;
        long out_i = 39L * (39L * (k_col - 1) + (j_col - 1)) + (i_col - 1);
        tmp = C0 * (orig[_in_i_col - 1] + orig[_in_i_col + 1] + orig[_in_i_col + 39] + orig[_in_i_col - 39] - 4 * orig[_in_i_col]) + C1 * (orig[_in_i_col - 38] + orig[_in_i_col + 38] + orig[_in_i_col + 1 - 39] + orig[_in_i_col - 1 - 39] - 4 * orig[_in_i_col]);
        sol[out_i] = tmp;
      }
    }
  }
/* Standardize from: for(k = 1;k < 40 - 1;k ++) {...} */
  loopk:
  for (k = 1; k < 40 - 1; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
    for (j = 1; j < 40 - 1; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
      for (i = 1; i < 40 - 1; i++) {
        idx = 39L * (39L * (k - 1) + (j - 1)) + (i - 1);
        km = 39L * (k - 1);
        jm = 39L * (j - 1);
        im = i - 1;
        kp = km + 39L;
        jp = jm + 39L;
        ip = im + 1;
        sol[idx] = ((2L * orig[idx]) - (orig[km + im] + orig[km + ip] + orig[jm + im] + orig[jm + ip] + orig[kp + im] + orig[kp + ip] + orig[jp + im] + orig[jp + ip])) / 32L;
      }
    }
  }
}