#pragma ACCEL kernel

void stencil(int orig[25][20][30],int sol[25][20][30],int filter[9][9][30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{2}
      for (p = 0; p < 30; p++) {
        sol[r][q][p] = 0;
        for (s = 0; s < 9; s++) {
          for (int t = 0; t < 9; t++) {
            sol[r][q][p] +=
              filter[s][t][p] * orig[r + -4 + s][q + -4 + t][0];
          }
        }
      }
    }
  }
//#pragma endscop
}