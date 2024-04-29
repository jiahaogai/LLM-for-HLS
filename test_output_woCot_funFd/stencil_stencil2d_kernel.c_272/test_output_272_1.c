<<<<<<< HEAD
#pragma ACCEL kernel
=======
Code: #pragma ACCEL kernel
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a

void stencil(int orig[400][400],int sol[400][400],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int idx;
  int idy;
  int tile;
  int ti;
  int tj;
  int fl;
=======
  int t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
<<<<<<< HEAD
  outer:
=======
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  for (i = 1; i < 400 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
    middle:
    for (j = 1; j < 400 - 1; j++) {
      idx = i - 1;
      idy = j - 1;
      tile = 0;
      inner:
      for (k = 0; k < 9; k++) {
        ti = idx + filter[k];
        tj = idy + filter[k + 1];
        if (ti >= 0 && ti < 400 && tj >= 0 && tj < 400) {
          tile += orig[ti][tj] * filter[k + 2];
        }
      }
      sol[i][j] = tile;
=======
    for (j = 1; j < 400 - 1; j++) {
      t = 0;
      for (k = 0; k < 9; k++) {
        t += filter[k] * orig[i + dx[k]][j + dy[k]];
      }
      sol[i][j] = t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}