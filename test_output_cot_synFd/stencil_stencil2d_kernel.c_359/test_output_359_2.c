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
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{14}
    middle:
    for (j = 0; j < 256; j++) {
      tmp_orig = 0;
      tmp_sol = 0;
      inner:
      for (k = -4; k < 5; k++) {
        index_orig = (i * 256 + j) * 256 + k;
        index_sol = (i * 256 + j) * 256 + k + 4;
        if ((((0 <= k) ? k : -k)) < 4) {
          tmp_orig = orig[index_orig];
          tmp_sol = sol[index_sol];
        }
        else {
          tmp_orig = orig[index_orig];
          tmp = tmp_sol << 1;
          if (tmp_orig > 0) {
            tmp_sol = tmp + 1;
          }
          else {
            tmp_sol = tmp;
          }
        }
      }
      sol[index_sol] = tmp_sol;
    }
  }
}