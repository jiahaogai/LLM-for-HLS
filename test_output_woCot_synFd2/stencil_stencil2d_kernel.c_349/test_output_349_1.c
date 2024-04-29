#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int tmp_orig;
  int tmp_sol;
  int filter_idx;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    tmp_orig = 0;
    tmp_sol = 0;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    inner:
    for (j = 0; j < 9; j++) {
      filter_idx = i - 4 + j;
      if (filter_idx < 0 || filter_idx > 8191) {
        tmp = 0;
      }
       else {
        tmp = filter[j];
      }
      tmp_orig += tmp * orig[filter_idx];
      tmp_sol += tmp * sol[filter_idx];
    }
    tmp_orig = tmp_orig + tmp_sol;
    tmp = tmp_orig;
    orig[i] = tmp;
    tmp_sol = 0.01 * tmp_orig - tmp_sol;
    sol[i] = tmp_sol;
  }
}