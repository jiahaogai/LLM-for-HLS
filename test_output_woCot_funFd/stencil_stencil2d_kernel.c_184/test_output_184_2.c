<<<<<<< HEAD
#pragma ACCEL kernel
=======
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int tmpp;
  int range_l;
  int range_r;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    tmp = 0;
    tmpp = i + 8;
    range_l = (tmpp > 8 ? tmpp : 8);
    tmpp += 7;
    range_r = (tmpp < 8192 ? tmpp : 8192);
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    inner:
    for (j = range_l; j < range_r; j++) {
      tmp += orig[j] * filter[j - i];
    }
    sol[i] = tmp;
  }
}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
