#pragma ACCEL kernel

<<<<<<< HEAD
void stencil(int orig[25][25],int sol[25][25],int filter[25][25])
{
  int i;
  int j;
=======
void stencil(int orig[4][4],int sol[4][4],int filter[4][4])
{
  int i;
  int j;
  int k;
//#pragma scop
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
<<<<<<< HEAD
  for (i = 1; i < 25 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 25 - 1; j++) {
      sol[i][j] = ((filter[0][0] * orig[i][j]) + (filter[0][1] * orig[i][j + 1]) + (filter[0][2] * orig[i][j + 2]) + (filter[1][0] * orig[i + 1][j]) + (filter[1][1] * orig[i + 1][j + 1]) + (filter[1][2] * orig[i + 1][j + 2]) + (filter[2][0] * orig[i + 2][j]) + (filter[2][1] * orig[i + 2][j + 1]) + (filter[2][2] * orig[i + 2][j + 2])) / 128;
    }
  }
=======
  for (i = 1; i < 4; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 4; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (k = 0; k < 4; k++) {
        sol[i][j] += filter[k][0] * orig[i + (-1 + k)][j];
        sol[i][j] += filter[k][1] * orig[i + (-1 + k)][j + 1];
        sol[i][j] += filter[k][2] * orig[i + (-1 + k)][j + 2];
        sol[i][j] += filter[k][3] * orig[i + (-1 + k)][j + 3];
      }
    }
  }
//#pragma endscop
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}