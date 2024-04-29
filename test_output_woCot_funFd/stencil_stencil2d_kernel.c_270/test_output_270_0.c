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
  int t;
  int pt = 4;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
<<<<<<< HEAD
  for (i = 0; i < 8; i++) {
=======
  for (i = 0; i < 8192; i++) {
    t = 0;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
<<<<<<< HEAD
    middle:
    for (j = 0; j < 8; j++) {
      idx = i * 8 + j;
      val = 0;
      
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{32}
      inner:
      for (k = 0; k < 9; k++) {
        val += filter[k] * orig[idx + ((k - 4) * 8)];
      }
      sol[idx] = val;
    }
=======
    inner:
    for (j = 0; j < 9; j++) {
      t += orig[i + (j - 4)] * filter[j];
    }
    sol[i] = t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}