#pragma ACCEL kernel

void stencil3d(double C0,double C1,double orig[2][2][2],double sol[2][2][2])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  for (r = 0; r < 2; r++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 2; q++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (p = 0; p < 2; p++) {
        for (s = 0; s < 2; s++) {
          sol[r][q][p] = C0 * orig[r][q][p] + C1 * (orig[r][q][(p + 1) % 2] + orig[r][q][(p + 2) % 2] + orig[r][q][(p + 3) % 2] + orig[r][q][(p + 4) % 2] + orig[r][q][(p + 5) % 2] + orig[r][q][(p + 6) % 2] + orig[r][q][(p + 7) % 2] + orig[r][q][(p + 8) % 2] + orig[r][q][(p + 9) % 2]);
        }
      }
    }
  }
//#pragma endscop
}