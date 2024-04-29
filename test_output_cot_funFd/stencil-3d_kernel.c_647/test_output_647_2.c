#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long ko;
  long jn;
  long in;
  long range;
  long col;
  long max;
  long min;
  long mid;
  long idx;
  long idx_col;
  long end;
  long start;
  long register_0;
  long register_1;
  long register_2;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  i = 2;
  j = 2;
  k = 2;
  k_col = 32;
  j_col = 32;
  i_col = 32;
  range = 1;
  while (range < 32) {
    range *= 2;
    ++range;
  }
  ++range;
  col = range;
  max = 33 - range;
  min = 1 + (-range);
  mid = 2 * range;
  end = 33 - 1;
  start = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  loop:
  for (i = start; i < end; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    jloop:
    for (j = start; j < end; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      kloop:
      for (k = start; k < end; k++) {
        idx = i * i_col + j * j_col + k * k_col;
        register_0 = orig[idx - i_col - j_col - k_col] + orig[idx - i_col - j_col + k_col] + orig[idx - i_col + j_col - k_col] + orig[idx - i_col + j_col + k_col] + orig[idx + i_col - j_col - k_col] + orig[idx + i_col - j_col + k_col] + orig[idx + i_col + j_col - k_col] + orig[idx + i_col + j_col + k_col];
        register_1 = orig[idx - i_col - j_col] + orig[idx - i_col + j_col] + orig[idx + i_col - j_col] + orig[idx + i_col + j_col];
        register_2 = orig[idx - i_col] + orig[idx + i_col];
        sol[idx] = (C0 * register_0 + C1 * register_1 + register_2) / 4;
      }
    }
  }
}