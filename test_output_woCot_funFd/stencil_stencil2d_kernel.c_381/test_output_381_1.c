<<<<<<< HEAD
#pragma ACCEL kernel
=======
#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{126}

#pragma ACCEL PARALLEL FACTOR=auto{1}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      val = orig[idx] + filter[0] * orig[idx - 8192] + filter[1] * orig[idx - 8192 + 1] + filter[2] * orig[idx - 8192 + 2] + filter[3] * orig[idx - 8192 + 3] + filter[4] * orig[idx - 8192 + 4] + filter[5] * orig[idx - 8192 + 5] + filter[6] * orig[idx - 8192 + 6] + filter[7] * orig[idx - 8192 + 7] + filter[8] * orig[idx - 8192 + 8];
      sol[idx] = val;
    }
  }
}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
