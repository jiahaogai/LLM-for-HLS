#pragma ACCEL kernel

<<<<<<< HEAD
void stencil(int orig[400][400],int sol[400][400],int filter[9])
=======
void stencil(int orig[40][40],int sol[40][40],int filter[9])
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int idx;
  int idy;
  int t;
=======
  int fr;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  outer:
  for (i = 1; i < 400 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    for (j = 1; j < 400 - 1; j++) {
      t = 0;
      idx = -1 * filter[0] + i;
      idy = -1 * filter[0];
      inner_idx:
      for (k = 0; k < 9; k++) {
        t += orig[idx][idy] * filter[k];
        idx++;
        idy++;
      }
      sol[i][j] = t;
=======
  for (i = 1; i < 39; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 39; j++) {
      sol[i][j] = 0;
      for (k = 0; k < 9; k++) {
        fr = filter[k];
        sol[i][j] += fr * orig[i + (-1 + (k >> 1))][j + (-1 + (k & 1))];
      }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}