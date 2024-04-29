#pragma ACCEL kernel

<<<<<<< HEAD
void stencil(char orig[25][25],char sol[25][25],char filter[25][25])
{
  int i;
  int j;
  int k;
//#pragma scop
=======
void stencil(double orig[4][4],double sol[4][4],double filter[2][2])
{
  int i;
  int j;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 1; i < 25 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 25 - 1; j++) {
      sol[i][j] = ((filter[0][0] * orig[i - 1][j - 1]) + (filter[0][1] * orig[i - 1][j]) + (filter[0][2] * orig[i - 1][j + 1]) + (filter[1][0] * orig[i][j - 1]) + (filter[1][1] * orig[i][j]) + (filter[1][2] * orig[i][j + 1]) + (filter[2][0] * orig[i + 1][j - 1]) + (filter[2][1] * orig[i + 1][j]) + (filter[2][2] * orig[i + 1][j + 1])) / 8.0;
    }
  }
//#pragma endscop
=======
  for (i = 0; i < 4; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 4; j++) {
      sol[i][j] = ((filter[0][0] * orig[i][j]) + (filter[0][1] * orig[i][(j + 1) % 4]) + (filter[1][0] * orig[i][(j + 2) % 4]) + (filter[1][1] * orig[i][(j + 3) % 4])) / 16.0;
    }
  }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}