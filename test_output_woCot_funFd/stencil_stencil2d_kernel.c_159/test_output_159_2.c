#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int t;
  int row;
  int col;
=======
  int idx;
  int s;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  outer:
  for (i = 0; i < 8; i++) {
=======
  for (i = 1; i < 8191; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
<<<<<<< HEAD
    inner:
    for (j = 0; j < 8; j++) {
      t = 0;
      inner_1:
      for (k = 0; k < 9; k++) {
        row = i + (-1 + k);
        col = j + (-1 + k);
        if (((row >= 0) && (row < 8)) && ((col >= 0) && (col < 8))) {
          t += orig[row * 8 + col] * filter[k];
        }
      }
      sol[i * 8 + j] = t;
    }
=======
    for (j = 1; j < 8191; j++) {
      s = 0.0;
      idx = -4;
      while (idx <= 4) {
        s += ((double )filter[++idx]) * orig[i + idx];
      }
      sol[j] = s;
    }
    sol[8192 - 1] = ((-1 * 0.5) * sol[0]) + ((1.0 * 0.5) * sol[1]);
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 8190; j >= 2; j--) {
      sol[j] = ((-1 * 0.5) * sol[j]) + ((1.0 * 0.5) * sol[j - 1]);
    }
    sol[0] = ((1.0 * 0.5) * sol[1]) + ((-1.0 * 0.5) * sol[0]);
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}