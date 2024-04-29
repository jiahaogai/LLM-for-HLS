#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[2][2])
{
  int i;
  int j;
  int flit;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 1; i < 4; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 4; j++) {
      flit = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (int k = 0; k < 2; k++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (int l = 0; l < 2; l++) {
          flit += filter[k][l] * orig[i + (-1 + k)][j + (-1 + l)];
        }
      }
      sol[i][j] = flit;
    }
  }
//#pragma endscop
}