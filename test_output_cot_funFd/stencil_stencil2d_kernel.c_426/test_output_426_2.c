#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int r;
  int c;
  int k1;
  int k2;
  int tmp;
  int mul;
  int tmp_orig;
  int tmp_sol;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loop_1:
/* Standardize from: for(r = 0; r < 128; r++) {...} */
  for (r = 0; r <= 127; r++) {
    16:
/* Standardize from: for(c = 0; c < 64; c++) {...} */
    for (c = 0; c <= 63; c++) {
      tmp = 0;
      mul = 1;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_2:
/* Standardize from: for(k2 = 0; k2 < 9; k2++) {...} */
      for (k2 = 0; k2 <= 8; k2++) {
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        loop_3:
/* Standardize from: for(k1 = 0; k1 < 9; k1++) {...} */
        for (k1 = 0; k1 <= 8; k1++) {
          mul *= filter[k1];
          tmp_orig = r * 64 + c + (-4) + k1;
          tmp_sol = r * 64 + c + (-4) + k2;
          tmp += orig[tmp_orig] * mul;
        }
      }
      sol[tmp_sol] = tmp;
    }
  }
}