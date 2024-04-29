#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
<<<<<<< HEAD
  int s;
//#pragma scop
=======
  int val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      s = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (k = -4; k <= 4; k++) {
        idx = (i - 1) * 8192 + (j - 1) + k;
        if (idx < 0) {
          idx = 0;
        }
        else if (idx > 8191) {
          idx = 8191;
        }
        s += orig[idx] * filter[k + 4];
      }
      sol[i * 8192 + j] = s;
    }
  }
//#pragma endscop
=======
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      val = 0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (256 + 1 + 8) * (k - 4) + (256 + 1 + 8) * j + i;
        val += filter[k] * orig[idx];
      }
      sol[i * 256 + j] = val;
    }
  }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}