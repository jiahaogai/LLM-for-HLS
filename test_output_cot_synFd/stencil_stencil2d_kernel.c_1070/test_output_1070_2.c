#pragma ACCEL kernel

void stencil(int orig[25][20][30],int sol[25][20][30],int filter[30])
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
      
#pragma ACCEL TILE FACTOR=auto{8}
      for (p = 0; p < 30; p++) {
        sol[r][q][p] = 0;
        for (s = 0; s < 30; s++) {
          sol[r][q][p] += filter[s] * orig[r][q][s];
        }
      }
    }
  }
//#pragma endscop
}