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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 256; j++) {
      tmp_orig = 0;
      tmp_sol = 0;
      inner:
      for (k = 0; k < 9; k++) {
        index_orig = (256 + i - 4) * 256 + (256 + j - 4) * 9 + k;
        index_sol = (256 + i - 4) * 256 + (256 + j - 4) * 1 + k;
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