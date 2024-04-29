#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
<<<<<<< HEAD
  int k;
  int t;
  int pt = 4;
=======
  int t;
  int row;
  int col;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 0; i < 8192; i++) {
    t = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    for (j = 0; j < 9; j++) {
      k = i - 4 + j;
      if (k < 0 || k > 8191) {
        t += filter[j] * 0;
      }
       else {
        t += filter[j] * orig[k];
      }
    }
    sol[i] = t;
=======
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    inner:
    for (j = 0; j < 8192; j++) {
      t = 0;
      row:
      for (row = i - 4; row <= i + 4; row++) {
        col:
        for (j = j - 4; j <= j + 4; j++) {
          t += orig[row * 8192 + j] * filter[row - i + 4 + 4 * (j - j)];
        }
      }
      sol[i * 8192 + j] = t;
    }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}