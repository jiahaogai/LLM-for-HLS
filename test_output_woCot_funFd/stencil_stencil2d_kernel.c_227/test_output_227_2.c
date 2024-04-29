#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int result;
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
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 8; j++) {
<<<<<<< HEAD
      result = 0;
      inner:
      for (k = 0; k < 9; k++) {
        result += orig[i * 8 + j] * filter[k];
      }
      sol[i * 8 + j] = result;
=======
      tmp_orig = 0;
      tmp_sol = 0;
      
#pragma ACCEL PARALLEL reduction=tmp_orig FACTOR=auto{1}
      inner:
      for (k = 0; k < 8; k++) {
        filter_elem = filter[k];
        tmp_orig = orig[i * 8 + k] * filter_elem;
        tmp_sol += tmp_orig;
      }
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{8}
      tmp = tmp_sol;
      sol[i * 8 + j] = tmp;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}