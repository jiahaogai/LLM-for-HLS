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
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8186; j++) {
      result = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{32}
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i + ((k - 4) > 0 ? (k - 4) : 0) + ((k - 4) < 0 ? -(k - 4) : 0) * 8192];
      }
      sol[i * 8192 + j] = result;
    }
=======
  outer:
  for (i = 0; i < 8192; i++) {
    tmp = 0;
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    inner:
    for (j = 0; j < 9; j++) {
      tmp += filter[j] * orig[i + (_J_STride * (j - 4))];
    }
    sol[i] = tmp;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}