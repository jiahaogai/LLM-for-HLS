#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long _in_;
  long _out_;
  long _tmp_ = 0L;
  long _tmp_0 = 0L;
  long _tmp_1 = 0L;
  long _tmp_2 = 0L;
  long _tmp_3 = 0L;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_j:
/* Standardize from: for(j = 1;j < 32 + 1 - 3;j++) {...} */
  for (j = 1L + 32L; j <= 32L + 1L - 3L; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_k:
/* Standardize from: for(k = 1;k < 32 + 1 - 3;k++) {...} */
    for (k = 1L + 32L; k <= 32L + 1L - 3L; k++) {
      idx = 0L;
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      loop_i:
      for (i = 1L + 1L; i <= 32L + 1L - 1L; i++) {
        _in_ = ((- 1L) * (orig[((i - 1L) * 32L * 32L) + ((j - 1L) * 32L) + (k - 1L)]));
        _tmp_ = 32L * 32L * (i - 1L);
        _out_ = _tmp_ + 32L * (j - 1L) + (k - 1L);
        sol[_out_] = _in_ + orig[_out_] + ((- 1L) * (orig[_out_ + _tmp_]));
        idx++;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k_1:
/* Standardize from: for(k = 1;k < 32 + 1 - 1;k++) {...} */
  for (k = 1L + 32L; k <= 32L + 1L - 1L; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j_1:
/* Standardize from: for(j = 1;j < 32 + 1 - 1;j++) {...} */
    for (j = 1L + 32L; j <= 32L + 1L - 1L; j++) {
      idx = 0L;
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      loop_i_1:
      for (i = 1L + 1L; i <= 32L + 1L - 1L; i++) {
        _in_ = ((- 1L) * (sol[((i - 1L) * 32L * 32L) + ((j - 1L) * 32L) + (k - 1L)])) + sol[((i - 1L) * 32L * 32L) + ((j - 1L) * 32L) + (k - 1L)];
        _tmp_0 = 32L * 32L * (i - 1L);
        _out_ = _tmp_0 + 32L * (j - 1L) + (k - 1L);
        sol[_out_] = _in_ + ((- 1L) * (sol[_out_ + 1L]));
        idx++;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_j_2:
/* Standardize from: for(j = 1;j < 32 + 1 - 1;j++) {...} */
  for (j = 1L + 32L; j <= 32L + 1L - 1L; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_k_2:
/* Standardize from: for(k = 1;k < 32 + 1 - 1;k++) {...} */
    for (k = 1L + 32L; k <= 32L + 1L - 1L; k++) {
      idx = 0L;
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      loop_i_2:
      for (i = 1L + 1L; i <= 32L + 1L - 1L; i++) {
        _in_ = ((- 1L) * (sol[((i - 1L) * 32L * 32L) + ((j - 1L) * 32L) + (k - 1L)])) + sol[((i - 1L) * 32L * 32L) + ((j - 1L) * 32L) + (k - 1L)];
        _tmp_1 = 32L * 32L * (i - 1L);
        _out_ = _tmp_1 + 32L * (j - 1L) + (k - 1L);
        sol[_out_] = _in_ + ((- 1L) * (sol[_out_ + 32L]));
        idx++;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k_3:
/* Standardize from: for(k = 1;k < 32 + 1 - 1;k++) {...} */
  for (k = 1L + 32L; k <= 32L + 1L - 1L; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j_3:
/* Standardize from: for(j = 1;j < 32 + 1 - 1;j++) {...} */
    for (j = 1L + 32L; j <= 32L + 1L - 1L; j++) {
      idx = 0L;
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      loop_i_3:
      for (i = 1L + 1L; i <= 32L + 1L - 1L; i++) {
        _in_ = ((- 1L) * (sol[((i - 1L) * 32L * 32L) + ((j - 1L) * 32L) + (k - 1L)])) + sol[((i - 1L) * 32L * 32L) + ((j - 1L) * 32L) + (k - 1L)];
        _tmp_2 = 32L * 32L * (i - 1L);
        _out_ = _tmp_2 + 32L * (j - 1L) + (k - 1L);
        sol[_out_] = _in_ + ((- 1L) * (sol[_out_ + 32L * 32L]));
        idx++;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k_4:
/* Standardize from: for(k = 1;k < 32 + 1 - 1;k++) {...} */
  for (k = 1L + 32L; k <= 32L + 1L - 1L; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j_4:
/* Standardize from: for(j = 1;j < 32 + 1 - 1;j++) {...} */
    for (j = 1L + 32L; j <= 32L + 1L - 1L; j++) {
      idx = 0L;
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      loop_i_4:
      for (i = 1L + 1L; i <= 32L + 1L - 1L; i++) {
        _in_ = ((- 1L) * (sol[((i - 1L) * 32L * 32L) + ((j - 1L) * 32L) + (k - 1L)])) + sol[((i - 1L) * 32L * 32L) + ((j - 1L) * 32L) + (k - 1L)];
        _tmp_3 = 32L * 32L * (i - 1L);
        _out_ = _tmp_3 + 32L * (j - 1L) + (k - 1L);
        sol[_out_] = _in_;
        idx++;
      }
    }
  }
}