#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
<<<<<<< HEAD
  int k;
  int t;
  int pad;
  pad = 1;
=======
  int t;
  int x;
  int y;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 0; i < 8; i++) {
=======
  outer:
  for (i = 0; i < 8192; i++) {
    t = 0;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
<<<<<<< HEAD
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (k = -4; k < 5; k++) {
        int idx = ((i * 8) + j) * 8 + k;
        t += filter[((k + 4) * 8) + 4] * orig[pad + idx];
      }
      sol[((i * 8) + j)] = t;
    }
=======
    inner:
    for (j = 0; j < 9; j++) {
      x = i - 4 + j;
      if ((((0 <= x) && (x < 8192))) && ((((0 <= filter[j]) && (filter[j] <= 255))))){
        t += ((orig[x]) * (filter[j]));
      }
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    sol[i] = t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}