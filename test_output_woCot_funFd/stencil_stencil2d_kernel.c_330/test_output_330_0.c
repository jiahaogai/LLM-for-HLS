#pragma ACCEL kernel

<<<<<<< HEAD
void stencil(int orig[4][4],int sol[4][4],int filter[2][2])
=======
void stencil(int orig[4][4],int sol[4][4],int filter[4][4])
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int l;
=======
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 1; i < 4 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 1; j < 4 - 1; j++) {
      sol[i][j] = 0;
      for (k = 0; k < 2; k++) {
        for (l = 0; l < 2; l++) {
          sol[i][j] += filter[k][l] * orig[i + k][j + l];
        }
=======
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 1; i < 4; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (j = 1; j < 4; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (k = 0; k < 4; k++) {
        sol[i][j] += filter[k][0] * orig[i + (-1 + k)][j];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
    }
  }
//#pragma endscop
}