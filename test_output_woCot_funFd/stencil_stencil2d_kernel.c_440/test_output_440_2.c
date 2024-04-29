#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int k_col;
  int k_row;
  int elem;
=======
  int idx;
  int idy;
  int t;
  int x;
  int y;
  x = 0;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  loopj:
/* Standardize from: for(j = 1;j < 64 + 1 - 4;j++) {...} */
  for (j = 1 + 4; j < 64 + 1; j++) {
=======
  y = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  while (y < 64) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
<<<<<<< HEAD
    loopk_col:
    for (k_col = 0; k_col < 9; k_col++) {
      elem = 0;
      
#pragma ACCEL PARALLEL reduction=elem FACTOR=auto{16}
      loopk_row:
      for (k_row = 0; k_row < 9; k_row++) {
        k = k_row * 9 + k_col;
        elem += filter[k] * orig[j * 64 + k_col];
      }
      sol[j * 64 + k_col] = elem;
    }
=======
    while (x < 128) {
      t = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{32}
      for (j = 0; j < 3; j++) {
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (i = 0; i < 3; i++) {
          idx = x + i - 1;
          idy = y + j - 1;
          if (idx < 0) {
            idx = 0;
          }
          
#if 0
          if (idx > 127) {
            idx = 127;
          }
          
#endif
          if (idy < 0) {
            idy = 0;
          }
          
#if 0
          if (idy > 63) {
            idy = 63;
          }
          
#endif
          t += filter[i + j * 3] * orig[idx + idy * 128];
        }
      }
      sol[x + y * 128] = t;
      x++;
    }
    x = 0;
    y++;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}