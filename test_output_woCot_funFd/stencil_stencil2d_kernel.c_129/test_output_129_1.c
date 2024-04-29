#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
<<<<<<< HEAD
  int t;
  int pt = 4;
=======
  int k;
  int t;
  int pad;
  pad = 1;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 0; i < 8192; i++) {
    t = 0;
    
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{4}
    for (j = 0; j < 9; j++) {
      t += orig[i + (j - 4)] * filter[j];
    }
    
#pragma ACCEL PARALLEL assignment=sol FACTOR=auto{1}
    sol[i] = t;
=======
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (k = -4; k < 5; k++) {
        t += filter[k + 4] * orig[i * 64 + (j * 8 + k) * 8];
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      sol[i * 64 + j * 8] = t;
    }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}