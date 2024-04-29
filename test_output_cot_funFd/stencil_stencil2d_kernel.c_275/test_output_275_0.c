#pragma ACCEL kernel

void stencil(int orig[25][20][30],int sol[25][20][30],int filter[3][3][30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 1; r < 25 - 1; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 1; q < 20 - 1; q++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (p = 1; p < 30 - 1; p++) {
        for (s = 0; s < 30; s++) {
          sol[r][q][p] = ((filter[0][0][s] * orig[r - 1][q - 1][s]) + (filter[0][1][s] * orig[r - 1][q][s]) + (filter[0][2][s] * orig[r - 1][q + 1][s]) + (filter[1][0][s] * orig[r][q - 1][s]) + (filter[1][1][s] * orig[r][q][s]) + (filter[1][2][s] * orig[r][q + 1][s]) + (filter[2][0][s] * orig[r + 1][q - 1][s]) + (filter[2][1][s] * orig[r + 1][q][s]) + (filter[2][2][s] * orig[r + 1][q + 1][s])) / 126;
        }
      }
    }
  }
//#pragma endscop
}