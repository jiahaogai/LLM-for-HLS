#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int r;
  int c;
  int k1;
  int k2;
  int r_col;
  int c_col;
  int i;
  int mul;
  int temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loop_r:
  for (r = 0; r < 32; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_c:
    for (c = 0; c < 32; c++) {
      temp = 0;
      loop_k1:
      for (k1 = -4; k1 <= 4; k1++) {
        r_col = r + k1;
        loop_k2:
        for (k2 = -4; k2 <= 4; k2++) {
          if ((((r_col >= 0) && (r_col < 32)) && ((c + k2 >= 0)) && ((c + k2) < 32)) && ((k1 == 0) && (k2 == 0))) 
            mul = 2;
          else {
            mul = 1;
          }
          temp += mul * orig[r_col * 32 + c + k2] * filter[k1 + 4];
        }
      }
      sol[r * 32 + c] = temp;
    }
  }
}