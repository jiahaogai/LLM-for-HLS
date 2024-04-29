#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int idx;
  int oidx;
  int sol_idx;
  int filter_idx;
  int val;
=======
  int result;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 256; j++) {
<<<<<<< HEAD
      sol_idx = i * 256 + j;
      val = 0;
      
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        filter_idx = k - 4;
        oidx = (i + filter_idx) * 256 + (j + filter_idx);
        val += orig[oidx] * filter[k];
      }
      sol[sol_idx] = val;
=======
      result = 0;
      inner:
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i + ((k - 4) << 8) + j];
      }
      sol[i + j] = result;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}