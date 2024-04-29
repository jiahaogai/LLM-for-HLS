#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int t;
  int row;
  int col;
  row = 0;
=======
  int idx;
  int val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  while (row < 32) {
    col = 0;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    while (col < 32) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{16}
      for (k = -4; k <= 4; k++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
        for (j = -4; j <= 4; j++) {
          i = row + k;
          int _in_bound_i = i >= 0 && i < 32;
          j = col + j;
          int _in_bound_j = j >= 0 && j < 32;
          int _in_bound = _in_bound_i && _in_bound_j;
          t += filter[k + 4] * orig[i * 32 + j] * (_in_bound ? 1 : 0);
        }
      }
      sol[row * 32 + col] = t;
      col++;
    }
    row++;
=======
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      val = orig[idx] + filter[0] * orig[idx - 8192] + filter[1] * orig[idx - 8192 + 1] + filter[2] * orig[idx - 8192 + 2] + filter[3] * orig[idx - 8192 + 3] + filter[4] * orig[idx - 8192 + 4] + filter[5] * orig[idx - 8192 + 5] + filter[6] * orig[idx - 8192 + 6] + filter[7] * orig[idx - 8192 + 7] + filter[8] * orig[idx - 8192 + 8];
      sol[idx] = val;
    }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}