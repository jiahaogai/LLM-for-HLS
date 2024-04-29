Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flit;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{128}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop:
/* Standardize from: for(i = 1; i < 8; i++) {...} */
  loop_i:
  for (i = 1; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop:
    for (j = 1; j < 8; j++) {
      row = (8 * i) - 1;
      col = (8 * j) - 1;
      flit = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      loop_k:
      for (k = 0; k < 9; k++) {
        flit += orig[row + k] * filter[k];
      }
      sol[col + 1] = flit;
    }
  }
//#pragma endscop
}