#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int r;
  int c;
  int k1;
  int k2;
  int k;
  int temp;
  int mul;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loop_1:
/* Standardize from: for(r = 0; r < 128; r++) {...} */
  for (r = 0; r <= 128 - 1; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_2:
/* Standardize from: for(c = 0; c < 64; c++) {...} */
    for (c = 0; c <= 64 - 1; c++) {
      temp = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_3:
/* Standardize from: for(k2 = 0; k2 < 9; k2++) {...} */
      for (k2 = 0; k2 <= 9 - 1; k2++) {
        
#pragma ACCEL PIPELINE auto{flatten}
        
#pragma ACCEL TILE FACTOR=auto{1}
        loop_4:
/* Standardize from: for(k1 = 0; k1 < 9; k1++) {...} */
        for (k1 = 0; k1 <= 9 - 1; k1++) {
          k = k1 + 9 * k2;
          mul = orig[r * 64 + c] * filter[k];
          temp += mul;
        }
      }
      sol[r * 64 + c] = temp;
    }
  }
}