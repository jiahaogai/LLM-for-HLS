#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int tmp;
  int bi;
  int bj;
  bi = 8;
  bj = 8;
=======
  int t;
  int pt = 4 * 9;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  outer:
  for (i = 0; i < 8192; i++) {
    tmp = 0;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    inner:
    for (j = 0; j < 9; j++) {
      tmp += orig[i + ((j - 4) * bi)] * filter[j];
    }
    sol[i] = tmp;
=======
  for (i = 4 + 8; i < 8192 - 8 - 4; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 4 + 8; j < 8192 - 8 - 4; j++) {
      t = 0;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (k = 0; k < 9; k++) {
        t += filter[k] * orig[i + ((k - 4) * 8192 / 4)];
      }
      sol[i * 8192 + j] = t;
    }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}