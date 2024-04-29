#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{2}

#pragma ACCEL PARALLEL FACTOR=auto{3}
void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long id = 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_k:
  for (k = 2; k < 392; k++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    loop_j:
    for (j = 2; j < 392; j++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      loop_i:
      for (i = 2; i < 392; i++) {
        i_col = i - 2;
        k_col = k - 2;
        id = (k_col * 392) + i_col;
        sol[id] = ((orig[id + 1] + orig[id - 1]) + (orig[id + 392] + orig[id - 392])) + (orig[id + 392 * 2] + orig[id - 392 * 2]) - (4 * orig[id]);
      }
    }
  }
}