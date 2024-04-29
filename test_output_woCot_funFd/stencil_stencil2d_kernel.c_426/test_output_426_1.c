Code: 
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int r;
  int r_col;
  int c;
  int c_col;
  int mul;
  int temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loop:for (i = 0; i < 128 + 2; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:for (j = 0; j < 64 + 2; j++) {
      r_col = i - 1;
      c_col = j - 1;
      temp = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopk:for (k = 0; k < 9; k++) {
        r = r_col + ((4 - 1) + (k / 3));
        c = c_col + ((4 - 1) + (k % 3));
        mul = orig[r * (64 + 2) + c] * filter[k];
        temp += mul;
      }
      sol[i * (64 + 2) + j] = temp;
    }
  }
}