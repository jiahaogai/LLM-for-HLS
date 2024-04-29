#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
<<<<<<< HEAD
  int s;
=======
  int center = 4;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  outer:
  for (i = 1; i < 8191; i++) {
<<<<<<< HEAD
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 1; j < 8191; j++) {
      s = 0;
      inner:
      for (k = -4; k < 5; k++) {
        idx = (8192 + i + k) % 8192;
        s += filter[4 + k] * orig[idx * 8192 + j];
      }
      sol[i * 8192 + j] = s;
=======
    middle:
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      sol[idx] = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      inner:
      for (k = 0; k < 9; k++) {
        sol[idx] += filter[k] * orig[idx + +(center - k)];
      }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}