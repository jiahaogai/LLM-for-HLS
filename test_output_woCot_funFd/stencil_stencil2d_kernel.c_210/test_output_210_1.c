#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
<<<<<<< HEAD
  int pad;
  pad = 1;
=======
  int row;
  int col;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PARALLEL reduction=orig FACTOR=auto{1}
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (k = 0; k < 8; k++) {
        t += orig[i * 8 + j] * filter[k];
      }
      sol[i * 8 + j] = t;
=======
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{8}
      inner:
      for (k = -4; k < 5; k++) {
        row = ((4 + i) + k) & 255;
        col = ((4 + j) - k) & 255;
        t += filter[((k + 4) << 3) + ((k + 4) > 7 ? 1 : 0)] * orig[row * 256 + col];
      }
      sol[i * 256 + j] = t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}