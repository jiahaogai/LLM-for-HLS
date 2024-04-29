#pragma ACCEL kernel

void stencil(int orig[25][20][3],int sol[25][20][3],int filter[9][3])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  for (r = 1; r < 25 - 1; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 1; q < 20 - 1; q++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (p = 1; p < 3 - 1; p++) {
        for (s = 0; s < 3; s++) {
          sol[r][q][p] = ((filter[0][s] * orig[r - 1][q][p]) + (filter[1][s] * orig[r][q][p]) + (filter[2][s] * orig[r + 1][q][p])) / 9;
        }
      }
    }
  }
//#pragma endscop
}