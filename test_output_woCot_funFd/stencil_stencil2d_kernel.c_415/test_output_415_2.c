<<<<<<< HEAD
The kernel is written in C99, and the ACCEL compiler accepts a subset of C99.
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
=======
#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int idx;
  int center = 45;
=======
  int k_col;
  int i_col;
  double sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
<<<<<<< HEAD
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      sol[idx] = ((filter[0] * orig[idx - 8192]) + (filter[1] * orig[idx - 8191]) + (filter[2] * orig[idx - 8190]) + (filter[3] * orig[idx - 8189]) + (filter[4] * orig[idx - 8188]) + (filter[5] * orig[idx - 8187]) + (filter[6] * orig[idx - 8186]) + (filter[7] * orig[idx - 8185]) + (filter[8] * orig[idx - 8184])) + orig[idx];
=======
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 8192; j++) {
      i_col = i - 4;
      k_col = 0;
      
      inner:
      while (k_col < 9) {
        k = k_col + i_col;
        if ((((i_col >= 0) && (i_col < 8)) && ((k_col >= 0) && (k_col < 8))) && ((k >= 0) && (k < 8192))) {
          sum = 0.0;
          elem:
          for (k_col = 0; k_col < 9; k_col++) {
            sum += filter[k_col] * orig[k];
            k++;
          }
          sol[j] = sum;
        }
        else {
          sol[j] = 0.0;
        }
      }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}