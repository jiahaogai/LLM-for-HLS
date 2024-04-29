#pragma ACCEL kernel

<<<<<<< HEAD
void stencil(double orig[25][25],double sol[25][25],double filter[25])
=======
void stencil(double orig[4][4],double sol[4][4],double filter[4][4])
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
=======
  int m;
  int n;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 0; i < 25; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 25; j++) {
      sol[i][j] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      for (k = 0; k < 25; k++) {
        sol[i][j] += filter[k] * orig[i][k] * orig[j][k];
=======
  for (i = 1; i < 4 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 4 - 1; j++) {
      sol[i][j] = 0.0;
      for (k = 0; k < 4; k++) {
        for (m = 0; m < 4; m++) {
          sol[i][j] += filter[k][m] * orig[i + k][j + m];
        }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
    }
  }
//#pragma endscop
}