#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int t;
  int pt = 4;
=======
  int ti;
  int tj;
  int tk;
  int idx;
  int val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 256; j++) {
<<<<<<< HEAD
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        int cur = orig[i * 256 + j] * filter[k];
        int ref = orig[(i + ((k / 3) - 1)) * 256 + (j + ((k % 3) - 1))] ;
        t += cur + ref;
      }
      sol[i * 256 + j] = t;
=======
      val = 0;
      inner:
      for (k = 0; k < 9; k++) {
        ti = i + ((k >> 4) & 3) - 1;
        tj = j + ((k >> 2) & 3) - 1;
        tk = k & 3;
        if (ti >= 0 && ti < 256 && tj >= 0 && tj < 256) {
          idx = ti * 256 + tj;
          val += orig[idx] * filter[tk];
        }
      }
      sol[i * 256 + j] = val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}