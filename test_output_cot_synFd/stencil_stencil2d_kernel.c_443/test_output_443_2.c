#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int bound;
  int flatten_bound;
  int range_l;
  int range_u;
  int pad;
  pad = 1;
  bound = 8;
  flatten_bound = bound + 2 * pad;
  range_l = pad - 1;
  range_u = bound - 1;
  for (i = range_l; i <= range_u; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{126}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = range_l; j <= range_u; j++) {
      idx = i * bound + j;
      sol[idx] = ((filter[0] * orig[idx]) + (filter[1] * (orig[idx + 1] + orig[idx - 1])) + (filter[2] * orig[idx + bound]) +
                  (filter[3] * (orig[idx + bound + 1] + orig[idx + bound - 1])) + (filter[4] * orig[idx + 2 * bound]) +
                  (filter[5] * (orig[idx + 2 * bound + 1] + orig[idx + 2 * bound - 1])) + (filter[6] * orig[idx + 3 * bound]) +
                  (filter[7] * (orig[idx + 3 * bound + 1] + orig[idx + 3 * bound - 1])) +
                  (filter[8] * orig[idx + 4 * bound])) / 64;
    }
  }
}