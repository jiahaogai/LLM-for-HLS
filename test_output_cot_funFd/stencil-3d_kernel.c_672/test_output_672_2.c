#pragma ACCEL kernel

void stencil(int n,int m,double A[25][20][30],double B[30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopr:
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopq:
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{2}
      loopp:
      for (p = 0; p < 30; p++) {
        double sum = 0.0;
        sloopi:
        for (s = 0; s < 30; s++) {
          sum += A[r][q][s] * B[s];
        }
        A[r][q][p] = sum;
      }
    }
  }
//#pragma endscop
}