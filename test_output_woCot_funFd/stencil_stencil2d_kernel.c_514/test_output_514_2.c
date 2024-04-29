#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int row;
  int col;
  int flen;
=======
  int idx;
  int val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  flen = 9;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  row = 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  loop_row:
  while (row < 81) {
    col = 0;
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_col:
    while (col < 81) {
      sol[row * 81 + col] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_k:
      for (k = 0; k < 9; k++) {
        i = row - 4 + k / 3;
        j = col - 4 + k % 3;
        sol[row * 81 + col] += orig[i * 81 + j] * filter[k];
      }
      col++;
    }
    row++;
=======
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      val = orig[idx] + filter[0] * orig[idx - 8192] + filter[1] * orig[idx - 8191] + filter[2] * orig[idx - 8190] + filter[3] * orig[idx - 8189] + filter[4] * orig[idx - 8188] + filter[5] * orig[idx - 8187] + filter[6] * orig[idx - 8186] + filter[7] * orig[idx - 8185] + filter[8] * orig[idx - 8184];
      sol[idx] = val;
    }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}