#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      t = 0;
      int k_col;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k_col = -4; k_col <= 4; k_col += 1) {
        int k_row;
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        for (k_row = -4; k_row <= 4; k_row += 1) {
          int k;
          k = (k_row * 8192) + k_col;
          t += filter[k + 4] * orig[k];
        }
      }
      sol[i * 8192 + j] = t;
    }
  }
//#pragma endscop
}