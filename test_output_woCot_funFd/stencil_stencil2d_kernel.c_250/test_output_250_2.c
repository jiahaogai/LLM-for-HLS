#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
<<<<<<< HEAD
  int k;
  int idx;
  int center;
=======
  int t;
  int x;
  int y;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      center = orig[idx];
      k = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      while (k < 9) {
        int offset = k - 4;
        int filter_idx = idx + (offset * 8192);
        sol[idx] += filter[k] * center - filter[k] * orig[filter_idx];
        k++;
      }
=======
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      t = 0;
      inner:
      for (x = -1; x <= 1; x++) {
        inner_1:
        for (y = -1; y <= 1; y++) {
          t += filter[((y + 1) * 3) + x + 1] * orig[i * 64 + j * 8 + x + ((y + 1) * 8)];
        }
      }
      sol[i * 64 + j * 8] = t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}