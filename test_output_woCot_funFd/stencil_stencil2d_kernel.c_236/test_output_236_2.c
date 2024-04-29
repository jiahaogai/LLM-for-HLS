<<<<<<< HEAD
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int tmp_orig;
  int tmp_sol;
  int index;
  int upper_bound;
  int lower_bound;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      tmp_orig = 0;
      tmp_sol = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      inner:
      for (k = -4; k < 5; k++) {
        index = ((i + k) << 8) + j;
        if ((((i + k) << 8) + j) < 0) {
          upper_bound = (((i + k) << 8) & 0xffffff00);
        }
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        else {
          if ((((i + k) << 8) + j) > 8191) {
            lower_bound = (8192 - (((i + k) << 8) & 0xffffff00)) << 8;
          }
          
#pragma ACCEL PARALLEL FACTOR=auto{8}
          else {
            lower_bound = 8;
          }
        }
        tmp = 0;
        
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{32}
        inner_bound:
        for (tmp = upper_bound; tmp < lower_bound; tmp++) {
          tmp += ((k == -4) || (k == 4)) ? 0 : filter[4 + k];
        }
        if (k == -4) {
          tmp_orig = tmp;
        }
        if (k == 4) {
          tmp_sol = tmp;
        }
      }
      orig[index] = tmp_orig;
      sol[index] = tmp_sol;
    }
  }
}
=======
Summary: Compilation failed.
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
