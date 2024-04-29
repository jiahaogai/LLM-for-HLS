#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{8}

#pragma ACCEL PARALLEL FACTOR=auto{1}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int tmp;
  int tmpp;
  int range = 32 + 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 32; i < 8168 + 32; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 32; j < 8168 + 32; j++) {
      tmp = 0;
      inner:
      for (k = -32; k < -1 + 32; k++) {
        tmpp = k + j;
        if (tmpp >= 32 && tmpp < 8168 + 32) {
          tmp += ((orig[tmpp]) * (filter[k + 32])) ;
        }
      }
      sol[i * (8192) + j] = tmp;
=======
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{8}
      for (k = -pad; k <= 8 - pad; k++) {
        t += filter[k + pad] * orig[i * 64 + (j * 8 + k)];
      }
      sol[i * 64 + j * 8] = t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}