#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[2][2])
{
  int r;
  int q;
  int p;
  int k1;
  int k2;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 4; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 4; q++) {
      sol[r][q] = 0;
      for (p = 0; p < 2; p++) {
        for (k1 = 0; k1 < 2; k1++) {
          int k2 = (p + 1 == 2) ? 0 : k1 + 1;
          sol[r][q] += filter[p][k1] * orig[r + p][q + k2];
        }
      }
    }
  }
//#pragma endscop
}