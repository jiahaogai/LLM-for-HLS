#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[2][2])
{
  int i;
  int j;
  int k;
  int l;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 1; i < 4 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 1; j < 4 - 1; j++) {
      sol[i][j] = 0;
      for (k = 0; k < 2; k++) {
        for (l = 0; l < 2; l++) {
          sol[i][j] += filter[k][l] * orig[i + k][j + l];
        }
      }
    }
  }
//#pragma endscop
}