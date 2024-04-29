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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (r = 2; r < 128 - 1; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{4}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (c = 2; c < 64 - 1; c++) {
      mul = 0;
      k_col = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      while (k_col < 3) {
        i_col = 0;
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        while (i_col < 3) {
          j_col = 0;
          
#pragma ACCEL PARALLEL reduction=mul FACTOR=auto{1}
          while (j_col < 3) {
            r_col = r - 1 + k_col;
            c_col = c - 1 + i_col;
            mul += filter[j_col++] * orig[r_col * 64 + c_col];
          }
          i_col++;
        }
        k_col++;
      }
      sol[r * 64 + c] = mul;
    }
  }
}