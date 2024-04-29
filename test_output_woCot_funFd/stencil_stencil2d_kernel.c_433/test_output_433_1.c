#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
<<<<<<< HEAD
  int flit;
=======
  int flatten_filter[81];
  int flatten_orig[8192];
  int flatten_sol[8192];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
  for (j = 0; j < 256; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 0; i < 256; i++) {
      i_col = ((256 + 1 - 2) + i) % 256;
      j_col = ((256 + 1 - 2) + j) % 256;
      flit = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      loopk:
      for (k = 0; k < 9; k++) {
        k_col = ((256 + 1 - 2) + k) % 256;
        flit += ((orig[i_col * 256 + j_col] * filter[k]) << 7);
      }
      sol[i * 256 + j] = flit >> 7;
    }
  }
=======
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8192; i++) {
    flatten_orig[i] = orig[i];
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 9; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 9; j++) {
      flatten_filter[i * 9 + j] = filter[i * 9 + j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 8; j++) {
      i_col = i * 128 + 128;
      j_col = j * 128 + 128;
      int sum = 0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
      for (k = 0; k < 9; k++) {
        
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
        for (k_col = 0; k_col < 9; k_col++) {
          int cur_filter = flatten_filter[k * 9 + k_col];
          int cur_orig = flatten_orig[(i_col + k_col) * 8192 + j_col + k];
          sum += cur_filter * cur_orig;
        }
      }
      flatten_sol[(i_col - 1) * 8192 + (j_col - 1)] = sum;
    }
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8192; i++) {
    sol[i] = flatten_sol[i];
  }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}