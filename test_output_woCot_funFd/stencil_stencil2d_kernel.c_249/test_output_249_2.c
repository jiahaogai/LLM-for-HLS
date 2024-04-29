#pragma ACCEL kernel

<<<<<<< HEAD
void stencil(int orig[25][25],int sol[25][25],int filter[25][25])
=======
void stencil(int orig[25][20],int sol[25][20],int filter[20])
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 25 - 1; i++) {
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 25 - 1; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 25; k++) {
        sol[i][j] += filter[k][0] * orig[i][j - 1 + k] + filter[k][1] * orig[i][j + k] + filter[k][2] * orig[i][j + 1 + k];
      }
=======
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 20 - 1; j++) {
      sol[i][j] = ((0 + filter[0]) * orig[i][j - 1] + (0 + filter[1]) * orig[i][j] + (0 + filter[2]) * orig[i][j + 1] + (0 + filter[3]) * orig[i - 1][j] + (1 + filter[4]) * orig[i][j] + (0 + filter[5]) * orig[i + 1][j] + (0 + filter[6]) * orig[i - 1][j - 1] + (0 + filter[7]) * orig[i - 1][j + 1] + (0 + filter[8]) * orig[i + 1][j - 1] + (0 + filter[9]) * orig[i + 1][j + 1]) / (0 + filter[4]);
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
//#pragma endscop
}