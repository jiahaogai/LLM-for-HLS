#pragma ACCEL kernel

void stencil3d(char C0,char C1,double orig[2][2][2],double sol[2][2][2])
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
        sol[i][j][k] = ((double )0);
        orig[i][j][k] += C0;
        sol[i][j][k] += orig[i][j][k];
        sol[i][j][k] += C1;
      }
    }
  }
//#pragma endscop
}