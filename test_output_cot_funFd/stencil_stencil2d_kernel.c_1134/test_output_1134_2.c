#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[2][2])
{
  int i;
  int j;
  int flit;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  for (i = 1; i < 4; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 1; j < 4; j++) {
      flit = 0;
      
#pragma ACCEL PARALLEL reduction = flit FACTOR=auto{1}
      for (int r = 0; r < 2; r++) {
        
#pragma ACCEL PARALLEL reduction = flit FACTOR=auto{1}
        for (int c = 0; c < 2; c++) {
          flit += orig[i + r - 1][j + c - 1] * filter[r][c];
        }
      }
      sol[i][j] = flit;
    }
  }
//#pragma endscop
}