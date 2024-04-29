#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int r;
  int c;
  int k1;
  int k2;
  int r_col;
  int c_col;
  int temp;
  int mul;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loop_r:
  for (r = 1; r < 8191; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_c:
    for (c = 1; c < 8191; c++) {
      mul = 0;
      loop_k1:
      for (k1 = 0; k1 < 9; k1++) {
        r_col = r + (-4 + k1);
        loop_k2:
        for (k2 = 0; k2 < 9; k2++) {
          c_col = c + (-4 + k2);
          temp = 0;
          if (((r_col >= 0) && (r_col < 8192)) && ((c_col >= 0) && (c_col < 8192))) {
            temp = orig[r_col * 8192 + c_col];
          }
          mul += filter[k1 * 9 + k2] * temp;
        }
      }
      sol[r * 8192 + c] = mul;
    }
  }
}