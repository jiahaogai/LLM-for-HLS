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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      sol_row = (i - 4 + 256) % 256;
      sol_col = (j - 4 + 256) % 256;
      orig_row = i;
      orig_col = j;
      sol[sol_row * 256 + sol_col] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      inner:
      for (k = 0; k < 9; k++) {
        filter_row = (4 - 1 + 8) % 8;
        filter_col = (4 - 1 + 8) % 8;
        i_col = orig_col + filter_col - k;
        j_col = orig_row + filter_row - k;
        if (i_col >= 0 && i_col < 256 && j_col >= 0 && j_col < 256) {
          sol[sol_row * 256 + sol_col] += orig[j_col * 256 + i_col] * filter[k];
        }
      }
    }
  }
//#pragma endscop
}