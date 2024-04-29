#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[4][4])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 0; i < 4; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (j = 0; j < 4; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (k = 0; k < 4; k++) {
        sol[i][j] += filter[k][j] * orig[i + k][j];
      }
    }
  }
//#pragma endscop
}