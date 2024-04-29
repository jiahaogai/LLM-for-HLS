#pragma ACCEL kernel

<<<<<<< HEAD
void stencil(int orig[4][4],int sol[4][4],int filter[4][4])
=======
void stencil(int orig[400][400],int sol[400][400],int filter[126][126])
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
=======
  int r;
  int s;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
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
=======
  for (i = 1; i < 400 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 400 - 1; j++) {
      sol[i][j] = 0.0;
      for (k = 0; k < 126; k++) {
        r = i - 63 + k;
        for (s = 0; s < 126; s++) {
          s = j - 63 + s;
          sol[i][j] += filter[k][s] * orig[r][s];
        }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
    }
  }
//#pragma endscop
}