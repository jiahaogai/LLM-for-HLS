#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
<<<<<<< HEAD
  int k;
  int t;
  int pt = 4;
=======
  int ti;
  int tj;
  int idx;
  int val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  outer:
  for (i = 0; i < 8192; i++) {
    t = 0;
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    inner:
    for (j = 0; j < 9; j++) {
      t += filter[j] * orig[i + ((j - 4) << 12)];
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    sol[i] = t;
=======
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 1; j < 8191; j++) {
      ti = ((8 * i) - 1) + 0;
      tj = ((8 * j) - 1) + 0;
      val = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      for (idx = 0; idx < 9; ++idx) {
        val += filter[idx] * orig[ti + _idx_[idx] + tj];
      }
      sol[i * 8192 + j] = val;
    }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}