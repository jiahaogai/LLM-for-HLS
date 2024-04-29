<<<<<<< HEAD
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
 
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
 void stencil(int orig[8192],int sol[8192],int filter[9])
=======
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
{
  int i;
  int j;
  int k;
  int idx;
<<<<<<< HEAD
  int val;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 337; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 337; j++) {
      idx = i * 337 + j;
      val = orig[idx] + filter[0] * orig[idx - 337 - 1] + filter[1] * orig[idx - 337] + filter[2] * orig[idx - 337 + 1] + filter[3] * orig[idx - 1] + filter[4] * orig[idx + 1] + filter[5] * orig[idx + 337 - 1] + filter[6] * orig[idx + 337] + filter[7] * orig[idx + 337 + 1];
      sol[idx] = val;
=======
  int centered_idx;
  int flattened_idx;
  int filtered_val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_i:
  for (i = 1; i < 33; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_j:
    for (j = 1; j < 33; j++) {
      idx = i * 32 + j;
      centered_idx = (i - 1) * 32 + (j - 1);
      flattened_idx = centered_idx;
//#pragma ACCEL PARALLEL reduction = sol FACTOR=auto{8}
      loop_k:
      for (k = 0; k < 9; k++) {
        filtered_val = orig[centered_idx + filter[k]];
        sol[flattened_idx] += filtered_val * filter[k];
      }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}