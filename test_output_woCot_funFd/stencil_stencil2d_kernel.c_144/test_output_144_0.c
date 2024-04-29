#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
 void stencil(int orig[8192],int sol[8192],int filter[9])
=======
void stencil(int orig[8192],int sol[8192],int filter[9])
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  loopj:
/* Standardize from: for(j = 1;j < 33 - 1;j++) {...} */
  for (j = 1 + 32; j-- > 32 - 1; ) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 33 - 1;k++) {...} */
    for (k = 1 + 32; k-- > 32 - 1; ) {
      idx = (j - 1) * 32 + k - 1;
      val = orig[idx] * filter[0];
      
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{1}
      loopi:
      for (i = 1; i < 33 - 1; i++) {
        val += orig[idx + i] * filter[i];
      }
=======
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      val = orig[idx] + filter[0] * orig[idx - 8192] + filter[1] * orig[idx - 8191] + filter[2] * orig[idx - 8190] + filter[3] * orig[idx - 8189] + filter[4] * orig[idx - 8188] + filter[5] * orig[idx - 8187] + filter[6] * orig[idx - 8186] + filter[7] * orig[idx - 8185] + filter[8] * orig[idx - 8184];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      sol[idx] = val;
    }
  }
}