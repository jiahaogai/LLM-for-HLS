#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int k_col;
  int k_row;
  int offset;
//#pragma scop
=======
  int sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
<<<<<<< HEAD
    middle:
    for (j = 0; j < 8192; j++) {
      offset = i * 8192 + j;
      sol[offset] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = k % 3;
        k_row = k / 3;
        sol[offset] += filter[k] * orig[offset + k_row * 8192 + k_col - 1];
      }
    }
  }
//#pragma endscop
=======
    inner:
    for (j = 0; j < 8192; j++) {
      sum = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      inner_reduction:
      for (k = -4; k < 5; k++) {
        sum += filter[((k + 4) >> 2)] * orig[i + k * 8];
      }
      sol[i * 8 + j] = sum;
    }
  }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}