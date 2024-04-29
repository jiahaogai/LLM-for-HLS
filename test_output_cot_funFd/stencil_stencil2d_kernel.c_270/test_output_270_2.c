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
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 8; j++) {
      tmp_orig = 0;
      tmp_sol = 0;
      inner:
      for (k = -4; k < 5; k++) {
        index_orig = i * 8 + j + k;
        index_sol = i * 8 + j;
        tmp_orig = orig[index_orig];
        tmp_sol += filter[4 + k] * tmp_orig;
      }
      sol[index_sol] = tmp_sol;
    }
  }
}