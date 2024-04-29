#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[4][4])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 1; i < 4; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 4; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{32}
      for (k = 0; k < 4; k++) {
        sol[i][j] += filter[k][0] * orig[i][j - 1 + k] + filter[k][1] * orig[i][j + k] + filter[k][2] * orig[i][j + 1 + k] + filter[k][3] * orig[i][j - 1 + 4 + k];
      }
    }
  }
//#pragma endscop
}