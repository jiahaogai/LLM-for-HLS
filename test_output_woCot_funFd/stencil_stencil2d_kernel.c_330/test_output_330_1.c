#pragma ACCEL kernel

<<<<<<< HEAD
void stencil(int orig[4][4],int sol[4][4],int filter[2][2])
{
  int i;
  int j;
  int x;
  int y;
=======
void stencil(int orig[4][4],int sol[4][4],int filter[4][4])
{
  int i;
  int j;
  int k;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 1; i < 4; i++) {
=======
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 1; i < 4 - 1; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
    for (j = 1; j < 4; j++) {
      x = ((filter[0][0] * orig[i - 1][j - 1]) + (filter[0][1] * orig[i - 1][j]) + (filter[0][2] * orig[i - 1][j + 1]) + (filter[1][0] * orig[i][j - 1]) + (filter[1][1] * orig[i][j]) + (filter[1][2] * orig[i][j + 1])) / 16;
      y = ((filter[0][0] * orig[i + 1][j - 1]) + (filter[0][1] * orig[i + 1][j]) + (filter[0][2] * orig[i + 1][j + 1]) + (filter[1][0] * orig[i][j - 1]) + (filter[1][1] * orig[i][j]) + (filter[1][2] * orig[i][j + 1])) / 16;
      sol[i][j] = x + y;
=======
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (j = 1; j < 4 - 1; j++) {
      sol[i][j] = ((filter[0][0] * orig[i - 1][j - 1]) + (filter[1][0] * orig[i - 1][j]) + (filter[2][0] * orig[i - 1][j + 1]) + (filter[3][0] * orig[i][j - 1]) + (filter[4][0] * orig[i][j]) + (filter[5][0] * orig[i][j + 1]) + (filter[6][0] * orig[i + 1][j - 1]) + (filter[7][0] * orig[i + 1][j]) + (filter[8][0] * orig[i + 1][j + 1])) + ((filter[0][1] * orig[i - 1][j - 1]) + (filter[1][1] * orig[i - 1][j]) + (filter[2][1] * orig[i - 1][j + 1]) + (filter[3][1] * orig[i][j - 1]) + (filter[4][1] * orig[i][j]) + (filter[5][1] * orig[i][j + 1]) + (filter[6][1] * orig[i + 1][j - 1]) + (filter[7][1] * orig[i + 1][j]) + (filter[8][1] * orig[i + 1][j + 1]));
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
//#pragma endscop
}