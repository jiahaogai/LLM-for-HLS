#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int tmp;
  int tmp_orig;
  int tmp_sol;
  int filter_elem;
=======
  int t;
  int pad;
  pad = 1;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
<<<<<<< HEAD
  for (i = 0; i < 256; i++) {
=======
  for (i = 0; i < 256 + 2 * 1; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
<<<<<<< HEAD
    for (j = 0; j < 256; j++) {
      tmp_orig = 0;
      tmp_sol = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = -4; k < 5; k++) {
        filter_elem = filter[4 + k];
        if (k == 4) {
          tmp_orig = orig[i * 256 + j];
          tmp_sol = tmp_orig * filter_elem;
        }
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        else {
          tmp = orig[i * 256 + j + k];
          tmp_sol += tmp * filter_elem;
        }
      }
      sol[i * 256 + j] = tmp_sol;
=======
    for (j = 0; j < 256 + 2 * 1; j++) {
      t = 0;
      inner:
      for (k = 0; k < 9; k++) {
        t += orig[i * (256 + 2 * 1) + j + ((k - 4) * (256 + 2 * 1)) - pad] * filter[k];
      }
      sol[i * (256 + 2 * 1) + j] = t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}