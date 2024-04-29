#pragma ACCEL kernel

void stencil3d(char C0,char C1,char orig[2][2][2],char sol[2][2][2])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 2; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 2; q++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{8}
      for (p = 0; p < 2; p++) {
        for (s = 0; s < 2; s++) {
          sol[r][q][p][s] = ((C0 * orig[r][q][p][s]) + (C1 * ((orig[r][q][1 + p][s] + orig[r][1 + q][p][s]) + orig[1 + r][q][p][s])));
        }
      }
    }
  }
//#pragma endscop
}