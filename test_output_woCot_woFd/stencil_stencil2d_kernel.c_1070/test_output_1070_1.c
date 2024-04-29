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
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{6}
      for (p = 0; p < 2; p++) {
        
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{2}
        for (k2 = 0; k2 < 2; k2++) {
          for (k1 = 0; k1 < 2; k1++) {
            sol[r][q] += filter[k2][k1] * orig[r + k1][q + k2];
          }
        }
      }
    }
  }
//#pragma endscop
}