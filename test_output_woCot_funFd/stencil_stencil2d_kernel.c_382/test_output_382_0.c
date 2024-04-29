#pragma ACCEL kernel

void stencil(int orig[25][20][3],int sol[25][20][3],int filter[20][3])
{
  int r;
  int q;
  int p;
  int d;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 1; r < 25 - 1; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 1; q < 20 - 1; q++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (p = 1; p < 3 - 1; p++) {
        for (d = 0; d < 3; d++) {
          sol[r][q][d] = filter[q][p] * orig[r][q][d] + (1 - filter[q][p]) * (sol[r][q - 1][d] + sol[r][q + 1][d] + sol[r - 1][q][d] + sol[r + 1][q][d]);
        }
      }
    }
  }
//#pragma endscop
}