#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
<<<<<<< HEAD
  int k;
  int tmp;
  int tmp_orig;
  int tmp_sol;
  int filter_idx;
=======
  int t;
  int x;
  int y;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      tmp_orig = 0;
      tmp = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      inner:
      for (k = 0; k < 9; k++) {
        filter_idx = i * 9 + k;
        tmp_sol = sol[(((j + 5) - 4) * 8 + ((i + 5) - 4)) - 256];
        tmp_orig = orig[(((j + 4) - 4) * 8 + ((i + 4) - 4)) - 256];
        tmp += filter[filter_idx] * tmp_sol;
        orig[(((j + 4) - 4) * 8 + ((i + 4) - 4)) - 256] = tmp_orig;
      }
      tmp = tmp + tmp;
      sol[(((j + 5) - 4) * 8 + ((i + 5) - 4)) - 256] = tmp;
=======
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 8; j < 8184; j += 8) {
      t = 0;
      x = i - 1;
      y = j - 1;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      while (x < i + 2) {
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        while (y < j + 2) {
          t += orig[x * 8192 + y] * filter[4 - (((x - i) + 1) + ((y - j) + 1)));
          y++;
        }
        y = j - 1;
        x++;
      }
      sol[i * 8192 + j] = t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}