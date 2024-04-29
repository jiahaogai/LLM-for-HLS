#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k1;
  int k2;
  int r;
  int c;
  int r_up;
  int r_down;
  int c_left;
  int c_right;
  int temp;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  r_up = 1;
  
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{1}
  r_down = 126;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
=======
#pragma ACCEL PARALLEL FACTOR=auto{16}
  r_down = 128 - 2;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  c_left = 1;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  c_right = 64;
  
#pragma ACCEL PIPELINE auto{off}
=======
  c_right = 64 - 2;
  
#pragma ACCEL PIPELINE auto{}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (r = 1; r < 128 - 1; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (c = 1; c < 64 - 1; c++) {
      temp = 0;
      
=======
  for (r = 0; r < 128; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (c = 0; c < 64; c++) {
      temp = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k1 = 0; k1 < 3; k1++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (k2 = 0; k2 < 3; k2++) {
          temp += filter[k1 * 3 + k2] * orig[r_up + k1 * 128 + c_left + k2];
        }
      }
      sol[r * 64 + c] = temp;
    }
  }
}