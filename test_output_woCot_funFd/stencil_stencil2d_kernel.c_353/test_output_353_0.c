#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
<<<<<<< HEAD
  int pt = 4;
=======
  int pad;
  pad = 1;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  outer:
  for (i = 0; i < 8192; i++) {
    t = 0;
    inner:
    for (j = 0; j < 9; j++) {
      k = i - 4 + j;
      t += orig[k] * filter[j];
    }
    sol[i] = t;
=======
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (k = -1 * pad; k <= 1 * pad; k++) {
        int cur;
        int flt;
        cur = orig[i * 8 + j] ;
        flt = filter[5 - k] ;
        t = t + cur * flt ;
      }
      sol[i * 8 + j] = t;
    }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}