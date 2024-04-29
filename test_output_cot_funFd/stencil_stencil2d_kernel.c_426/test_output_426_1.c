#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int r;
  int c;
  int k1;
  int k2;
  int temp;
  int mul;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loopj1:
/* Standardize from: for(r = 0; r < 128; r++) {...} */
  for (r = 0; r <= 127; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj2:
/* Standardize from: for(c = 0; c < 64; c++) {...} */
    for (c = 0; c <= 63; c++) {
      temp = 0;
      mul = 1;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopj3:
/* Standardize from: for(k2 = 0; k2 < 9; k2++) {...} */
      for (k2 = 0; k2 <= 8; k2++) {
        
#pragma ACCEL PIPELINE auto{flatten}
        
#pragma ACCEL TILE FACTOR=auto{1}
        loopj4:
/* Standardize from: for(k1 = 0; k1 < 9; k1++) {...} */
        for (k1 = 0; k1 <= 8; k1++) {
          mul *= filter[k1];
          temp += orig[r * 64 + c * 1 + k1] * mul;
        }
      }
      sol[r * 64 + c] = temp;
    }
  }
}