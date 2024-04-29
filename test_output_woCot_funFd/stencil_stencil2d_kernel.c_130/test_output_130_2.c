#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int sum;
  int pad;
=======
  int tmp;
  int bi;
  int bj;
  bi = 0;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  pad = 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8; i++) {
=======
  loop_bi:
  for ( ; bi < 8; bi++) {
    bj = 0;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
<<<<<<< HEAD
    for (j = 0; j < 8; j++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{32}
      for (k = -1; k <= 1; k++) {
        sum += filter[k + 1] * orig[((i * 8) + j) * 8 + pad + k];
      }
      sol[((i * 8) + j) * 8 + pad] = sum;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  pad = 4;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 8; j++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      for (k = -1; k <= 1; k++) {
        sum += filter[k + 1] * sol[(((i * 8) + j) * 8 + pad) + k];
      }
      sol[((i * 8) + j) * 8 + pad] = sum;
=======
    loop_bj:
    for ( ; bj < 8; bj++) {
      tmp = 0;
      loop_k:
      for (k = -4; k <= 4; k++) {
        tmp += filter[4 + k] * orig[bi * 64 + bj * 8 + k];
      }
      sol[bi * 64 + bj * 8 + 4] = tmp;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}