#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int tmp;
  int t_out;
  int t_in;
=======
  int idx;
  int idy;
  int t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
<<<<<<< HEAD
    middle:
    for (j = 0; j < 256; j++) {
      t_out = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      inner:
      for (k = -4; k < 5; k++) {
        t_in = 0;
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        int_in:
        for (tmp = 0; tmp < 8; tmp++) {
          t_in += orig[(((i + tmp) + 256) % 256) * 256 + ((j + k + 256) % 256)];
        }
        filter_in:
        for (tmp = 0; tmp < 9; tmp++) {
          t_out += filter[tmp] * t_in;
        }
      }
      sol[i * 256 + j] = t_out;
=======
    inner:
    for (j = 0; j < 256; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      filter:
      for (k = 0; k < 9; k++) {
        idx = i + (-4 + k);
        idy = j + (-4 + k);
        if (idx < 0 || idx > 255 || idy < 0 || idy > 255) {
          t += filter[k] * 0;
        }
         else {
          t += filter[k] * orig[idx * 256 + idy];
        }
      }
      sol[i * 256 + j] = t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}