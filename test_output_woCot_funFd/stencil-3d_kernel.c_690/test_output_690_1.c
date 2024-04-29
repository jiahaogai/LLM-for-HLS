#pragma ACCEL kernel

void stencil3d(char C0,char C1,char orig[2][2][2],char sol[2][2][2])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 2; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    for (j = 0; j < 2; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (k = 0; k < 2; k++) {
        sol[i][j][k] = ((C0 * orig[i][j][k]) + (C1 * (((orig[i - 1][j][k] + orig[i + 1][j][k]) + (orig[i][j - 1][k] + orig[i][j + 1][k])) + (orig[i][j][k - 1] + orig[i][j][k + 1])))) / 4;
      }
    }
  }
//#pragma endscop
}