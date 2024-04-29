#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
<<<<<<< HEAD
  int k;
  int tmp;
  int t;
  int fs = 0;
=======
  int t;
  int pad;
  pad = 1;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  outer:
  for (i = 0; i < 8192; i++) {
    tmp = 0;
    
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{16}
    inner:
    for (k = 0; k < 9; k++) {
      t = orig[fs + ((k - 4) * 64)];
      tmp += filter[k] * t;
    }
    sol[i] = tmp;
    fs++;
=======
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 8; j++) {
      t = 0;
      int k;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        t += filter[k] * orig[(((i + pad) * 64) + ((j + pad) * 8)) + k];
      }
      sol[((i * 64) + (j * 8)) + 0] = t;
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 8; j++) {
      t = 0;
      int k;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (k = 0; k < 9; k++) {
        t += filter[k] * sol[(((i + pad) * 64) + ((j + pad) * 8)) + k];
      }
      sol[((i * 64) + (j * 8)) + 0] = t;
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 8; j++) {
      t = 0;
      int k;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        t += filter[k] * sol[(((i + pad) * 64) + ((j + pad) * 8)) + k];
      }
      sol[((i * 64) + (j * 8)) + 0] = t;
    }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}