#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
<<<<<<< HEAD
  int oidx;
  int fi;
=======
  int val;
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
    inner:
    for (j = 0; j < 256; j++) {
      oidx = i * 256 + j;
      sol[oidx] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      inner_filter:
      for (k = 0; k < 9; k++) {
        fi = filter[k];
        idx = oidx + ((k - 4) * 256);
        sol[oidx] += fi * orig[idx];
      }
=======
    middle:
    for (j = 0; j < 256; j++) {
      val = 0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (256 + i - 4) * 256 + (256 + j - 4) * 9 + k;
        val += orig[idx] * filter[k];
      }
      sol[i * 256 + j] = val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}