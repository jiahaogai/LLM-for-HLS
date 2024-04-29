#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int k_col;
  int i_col;
  int j_col;
  int t;
=======
  int result;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      inner:
      for (k = -4; k < 5; k++) {
        i_col = i + k;
        if (((i_col >= 0) && (i_col < 256))) {
          j_col = j - 4;
          outer_col:
          while (1) {
            if ((j_col < 0) || (j_col >= 256)) {
              break;
            }
            k_col = k + 4;
            if (((i_col >= 0) && (i_col < 256)) && ((j_col >= 0) && (j_col < 256))) {
              t += ((orig[i_col * 256 + j_col] * filter[k_col]) >> 4);
            }
            j_col++;
          }
        }
      }
      sol[i * 256 + j] = t;
=======
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 1; j < 8191; j++) {
      result = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i + ((k - 4) * 8191)];
      }
      sol[i * 8191 + j] = result;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}