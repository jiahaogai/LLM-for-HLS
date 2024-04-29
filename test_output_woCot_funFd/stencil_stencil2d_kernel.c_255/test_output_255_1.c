#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[3][3])
{
  int i;
  int j;
  int k;
  int l;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 4; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 4; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (k = 0; k < 3; k++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{2}
        for (l = 0; l < 3; l++) {
          sol[i][j] += filter[k][l] * orig[i + -1 + k][j + -1 + l];
        }
      }
    }
  }
//#pragma endscop
}