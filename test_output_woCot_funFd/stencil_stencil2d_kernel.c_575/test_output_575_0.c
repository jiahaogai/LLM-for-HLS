#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{2}
=======
#pragma ACCEL PARALLEL FACTOR=auto{1}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      
<<<<<<< HEAD
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = k - 4;
        i_col = i + k_col;
        if (((i_col >= 0) && (i_col < 256))) {
          
#pragma ACCEL PIPELINE auto{off}
          
#pragma ACCEL TILE FACTOR=auto{1}
          
#pragma ACCEL PARALLEL FACTOR=auto{1}
          inner_middle:
          for (j_col = 0; j_col < 9; j_col++) {
            int tmp;
            k_col = k_col - 4;
            i_col = i_col - 4;
            j_col = j_col - 4;
            if (((i_col >= 0) && (i_col < 256) && (j_col >= 0) && (j_col < 256))) {
              tmp = orig[i_col * 256 + j_col];
            }
             else {
              tmp = 0;
            }
            t += filter[k * 9 + j_col] * tmp;
          }
        }
=======
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{8}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((k + i - 4) % 256);
        i_col = ((k_col + 1) % 256);
        j_col = ((j + 1) % 256);
        t += filter[k] * orig[i_col * 256 + j_col];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
      sol[i * 256 + j] = t;
    }
  }
}