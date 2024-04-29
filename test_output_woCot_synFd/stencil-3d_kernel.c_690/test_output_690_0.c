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
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 2; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{8}
      for (k = 0; k < 2; k++) {
        sol[i][j][k] = ((C0 * orig[i][j][k]) + (C1 * (orig[i][1 + j][k] + orig[1 + i][j][k] + orig[i][j][1 + k] + orig[1 + i][1 + j][k])));
      }
    }
  }
//#pragma endscop
}