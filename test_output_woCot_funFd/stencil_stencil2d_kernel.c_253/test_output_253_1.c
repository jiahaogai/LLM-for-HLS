#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int k_col;
  int buf[9];
=======
  int sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
<<<<<<< HEAD
  outer:
  for (i = 0; i < 8192; i++) {
    mid:
    for (j = 0; j < 9; j++) {
      buf[j] = orig[i - 4 + j];
    }
    inner:
    for (j = 0; j < 9; j++) {
      k_col = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      inner_par:
      for (k = 0; k < 9; k++) {
        sol[i] += buf[k] * filter[k_col++];
      }
=======
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      sum = 0.0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{4}
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (k = 0; k < 8; k++) {
        sum += filter[k] * orig[i + (-4 + k) * 8192] * orig[j + (-4 + k) * 8192];
      }
      sol[i * 8192 + j] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}