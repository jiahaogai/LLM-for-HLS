#pragma ACCEL kernel

void stencil(int orig[25][25],int sol[25][25],int filter[25])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (i = 1; i < 25 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 1; j < 25 - 1; j++) {
      sol[i][j] = ((0 + filter[0]) * orig[i][j]) + ((0 + filter[1]) * orig[i][j + 1]) + ((0 + filter[2]) * orig[i][j + 2]) + ((0 + filter[3]) * orig[i][j + 3]) + ((0 + filter[4]) * orig[i][j + 4]) + ((0 + filter[5]) * orig[i][j + 5]) + ((0 + filter[6]) * orig[i][j + 6]) + ((0 + filter[7]) * orig[i][j + 7]) + ((0 + filter[8]) * orig[i][j + 8]);
    }
  }
//#pragma endscop
}