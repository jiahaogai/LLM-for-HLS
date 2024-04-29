#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[4][4])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 4 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 4 - 1; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 4; k++) {
        sol[i][j] += filter[k][0] * orig[i + (-1 + k)][j];
        sol[i][j] += filter[k][1] * orig[i + 1 + k][j];
        sol[i][j] += filter[k][2] * orig[i + 2 + k][j];
        sol[i][j] += filter[k][3] * orig[i + 3 + k][j];
      }
    }
  }
//#pragma endscop
}