#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int r;
  int c;
  int k1;
  int k2;
  int r_col;
  int c_col;
  int tmp;
  int mul;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loop_r:
  for (r = 1; r < 8191; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_c:
    for (c = 1; c < 8191; c++) {
      r_col = r - 1;
      c_col = c - 1;
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{9}
      loop_k1:
      for (k1 = 0; k1 < 9; k1++) {
        mul = orig[r_col * 8192 + c_col * 9 + k1] * filter[k1];
        tmp += mul;
      }
      sol[r * 8192 + c] = tmp;
    }
  }
}