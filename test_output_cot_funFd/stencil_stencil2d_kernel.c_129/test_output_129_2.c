#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int ti;
  int tj;
  int tmp;
  int tmp_orig;
  int tmp_sol;
  int filter_elem;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      tmp_orig = 0;
      tmp_sol = 0;
      inner:
      for (filter_elem = 0; filter_elem < 9; filter_elem++) {
        ti = i + ((4 - 2) + (filter_elem % 3));
        tj = j + ((4 - 2) + (filter_elem / 3));
        tmp_orig += orig[ti * 8 + tj] * filter[filter_elem];
        tmp_sol += sol[ti * 8 + tj] * filter[filter_elem];
      }
      tmp = tmp_orig - tmp_sol;
      if (tmp < 0) {
        tmp = 0;
      }
      sol[i * 8 + j] = tmp;
    }
  }
}