#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int idx;
  int val;
=======
  int tmp;
  int tmp_orig;
  int tmp_sol;
  int filter_elem;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
<<<<<<< HEAD
  for (i = 0; i < 256; i++) {
=======
  for (i = 0; i < 8192; i++) {
    tmp_orig = 0;
    tmp_sol = 0;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
<<<<<<< HEAD
    middle:
    for (j = 0; j < 256; j++) {
      val = 0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (256 + i - 4) * 256 + (256 + j - 4) * 9 + k;
        val += orig[idx] * filter[k];
      }
      sol[i * 256 + j] = val;
    }
=======
    inner:
    for (j = 0; j < 9; j++) {
      filter_elem = filter[j];
      tmp = orig[i + (j - 4)];
      tmp_orig += filter_elem * tmp;
      tmp_sol += filter_elem * tmp;
    }
    sol[i] = tmp_sol;
    orig[i] = tmp_orig;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}