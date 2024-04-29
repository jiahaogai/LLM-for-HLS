#pragma ACCEL kernel

void stencil(char orig[4][4],char sol[4][4],char filter[4][4])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 4; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 4; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 4; k++) {
        sol[i][j] += filter[k][j] * orig[i][k];
      }
    }
  }
//#pragma endscop
}