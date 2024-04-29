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
  int orig_row;
  int orig_col;
  int sol_row;
  int sol_col;
  int filter_row;
  int filter_col;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 256; j++) {
      sol_col = sol[j];
      orig_col = orig[j];
      filter_col = filter[0] * orig_col;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        k_col = k * 256;
        i_col = i_col + 1;
        j_col = k_col + j_col;
        orig_row = i_col * 256;
        filter_row = k_col + filter[k];
        sol_row = orig_row;
        sol[sol_row] = sol[sol_row] + filter_col + filter[k] * orig[orig_row + j_col];
      }
    }
  }
//#pragma endscop
}