#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int tmp;
  int bi;
  int bj;
  bi = 0;
=======
  int sum;
  int idx;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  loop_bi:
  while (bi < 8) {
    bj = 0;
=======
  outer:
  for (i = 0; i < 256; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loop_bj:
    while (bj < 8) {
      tmp = 0;
      loop_k:
      for (k = -4; k < 5; k++) {
        tmp += filter[k + 4] * orig[bi * 64 + bj * 8 + k];
      }
      sol[bi * 64 + bj * 8 + 4] = tmp;
      bj++;
    }
    bi++;
=======
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      sum = 0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (256 + orig[i + ((k - 4) << 8)] - filter[k]) % 256;
        sum += orig[idx + (j << 8)] * filter[k];
      }
      sol[i + (j << 8)] = sum;
    }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}