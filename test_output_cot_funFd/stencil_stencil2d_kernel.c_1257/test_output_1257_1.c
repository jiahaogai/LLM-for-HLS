#pragma ACCEL kernel

void stencil(int orig[25][20][30],int sol[25][20][30],int filter[9][9][30])
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
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (p = 1; p < 30 - 1; p++) {
        for (s = 0; s < 30; s++) {
          sol[r][q][p] = ((0 + filter[4][4][s]) * orig[r][q][p]) + ((-1 * filter[4][0][s]) * (orig[r][q][p - 1])) + ((-1 * filter[0][4][s]) * (orig[r][q - 1][p])) + ((-1 * filter[0][0][s]) * (orig[r][q - 1][p - 1]));
        }
      }
    }
  }
//#pragma endscop
}