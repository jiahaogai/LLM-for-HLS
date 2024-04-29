#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int tmp_orig;
  int tmp_sol;
  int index_orig;
  int index_sol;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 1; j < 8191; j++) {
      tmp_orig = 0;
      tmp_sol = 0;
      inner:
      for (k = 0; k < 9; k++) {
        index_orig = (i - 4) * 8192 + (j - 4) * 9 + k;
        index_sol = (i - 4) * 8192 + (j - 4) * 1 + k;
        tmp_orig += orig[index_orig] * filter[k];
        tmp_sol += sol[index_sol] * filter[k];
      }
      tmp = tmp_orig - tmp_sol;
      if (tmp < 0) {
        tmp = 0;
      }
      sol[index_sol] = tmp;
    }
  }
}