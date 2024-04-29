#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int idx;
  int s;
=======
  int buf[9];
  int idx = 0;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
<<<<<<< HEAD
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 256; j++) {
      s = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (256 * (k - 4)) + j;
        s += filter[k] * orig[i * 256 + idx];
      }
      sol[i * 256 + j] = s;
=======
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      idx = i * 256 + j;
      inner:
      for (k = 0; k < 9; k++) {
        buf[k] = orig[idx + neigh[k]];
      }
      sol[idx] = solve(buf,filter);
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}