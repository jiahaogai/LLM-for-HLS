The ACCEL compiler is not required to make use of these directives. It is, however, recommended that you use these directives to help maximize hardware implementation performance.
#pragma ACCEL kernel

void stencil(int orig[25][20][3],int sol[25][20][3])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  for (r = 1; r < 25 - 1; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 1; q < 20 - 1; q++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (p = 1; p < 3; p++) {
        for (s = 0; s < 3; s++) {
          sol[r][q][p] = ((0.1 * (orig[r - 1][q][s] + orig[r + 1][q][s] + orig[r][q - 1][s] + orig[r][q + 1][s] + orig[r][q][s - 1] + orig[r][q][s + 1])) + (0.5 * orig[r][q][s])) + 2 * sol[r][q][s];
        }
      }
    }
  }
//#pragma endscop
}