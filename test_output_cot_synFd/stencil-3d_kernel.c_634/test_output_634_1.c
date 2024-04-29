#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{2}
void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long tid;
  long pad;
  long pad2;
  long flatten_i;
  long flatten_j;
  long flatten_k;
  long result;
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  loop_k:
  for (k = 0; k < 40; k++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    loop_j:
    for (j = 0; j < 40; j++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_i:
      for (i = 0; i < 40; i++) {
        tid = k * 40 * 40 + j * 40 + i;
        pad = 4 * 40 * 40;
        pad2 = pad + 2;
        flatten_i = i - 2 + pad2;
        flatten_j = j - 2 + pad2;
        flatten_k = k - 2 + pad2;
        result = C0 * (orig[tid + pad] + orig[tid + pad + 1] + orig[tid + pad + 2] + orig[tid + 1 + pad] + orig[tid + 1 + pad + 1] + orig[tid + 1 + pad + 2] + orig[tid + 2 + pad] + orig[tid + 2 + pad + 1] + orig[tid + 2 + pad + 2]) + C1 * (orig[tid] + orig[tid + 1] + orig[tid + 2] + orig[tid + pad2] + orig[tid + pad2 + 1] + orig[tid + pad2 + 2] + orig[tid + 1 + pad2] + orig[tid + 1 + pad2 + 1] + orig[tid + 1 + pad2 + 2] + orig[tid + 2 + pad2] + orig[tid + 2 + pad2 + 1] + orig[tid + 2 + pad2 + 2]);
        sol[tid] = result;
      }
    }
  }
}