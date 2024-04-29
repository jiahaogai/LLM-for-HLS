#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long s;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_k:
  for (k = 0; k < 40; k++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_j:
    for (j = 0; j < 40; j++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_i:
      for (i = 0; i < 40; i++) {
        idx = i + 40 * (j + 40 * k);
        s = orig[idx] + ((i > 0) ? orig[idx - 1] : 0) + ((j > 0) ? orig[idx - 40] : 0) + ((k > 0) ? orig[idx - 1600] : 0) + ((i < 39) ? orig[idx + 1] : 0) + ((j < 39) ? orig[idx + 40] : 0) + ((k < 39) ? orig[idx + 1600] : 0) - 2 * orig[idx];
        sol[idx] = s;
      }
    }
  }
}