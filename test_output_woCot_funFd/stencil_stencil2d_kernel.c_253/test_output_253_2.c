#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int batch;
<<<<<<< HEAD
  int batch_col;
=======
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{4}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 256; j++) {
      int sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
<<<<<<< HEAD
        int k_col = i - 4 + k;
        batch = k_col / 32;
        int batch_col = k_col - batch * 32;
        sum += filter[k] * orig[batch * 32 + batch_col * 256 + j];
=======
        int k_row = i - 4 + k / 3;
        int k_col = j - 4 + k % 3;
        if (k_row < 0 || k_row > 255 || k_col < 0 || k_col > 255) {
          continue;
        }
        else {
          int index = k_row * 256 + k_col;
          sum += filter[k] * orig[index];
        }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
      sol[i * 256 + j] = sum;
    }
  }
}