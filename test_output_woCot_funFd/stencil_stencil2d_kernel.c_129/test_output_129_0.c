#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 8191; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      for (x = -1 + -16; x < 1 + -16; x++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{16}
        for (y = -1 + -16; y < 1 + -16; y++) {
          t += filter[x + 16] * orig[i + x + ((j + y) * 8192)];
        }
      }
      sol[i + j * 8192] = t;
=======
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 1; j < 8191; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (x = -4; x < 5; x++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (y = -4; y < 5; y++) {
          t += filter[4 + x] * orig[i + x][j + y];
        }
      }
      sol[i][j] = t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}