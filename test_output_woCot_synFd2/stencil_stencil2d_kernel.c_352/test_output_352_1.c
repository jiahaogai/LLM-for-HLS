#pragma ACCEL kernel

void stencil(int orig[25][25],int sol[25][25],int filter[25])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 25 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 25 - 1; j++) {
      sol[i][j] = ((0 + filter[0]) * orig[i][j] + (1 + filter[1]) * orig[i][j + 1] + (2 + filter[2]) * orig[i][j + 2] + (3 + filter[3]) * orig[i][j + 3] + (4 + filter[4]) * orig[i][j + 4] + (5 + filter[5]) * orig[i][j + 5] + (6 + filter[6]) * orig[i][j + 6] + (7 + filter[7]) * orig[i][j + 7] + (8 + filter[8]) * orig[i][j + 8] + (9 + filter[9]) * orig[i][j + 9]) / ((0 + filter[0]) + (1 + filter[1]) + (2 + filter[2]) + (3 + filter[3]) + (4 + filter[4]) + (5 + filter[5]) + (6 + filter[6]) + (7 + filter[7]) + (8 + filter[8]) + (9 + filter[9]));
    }
  }
//#pragma endscop
}