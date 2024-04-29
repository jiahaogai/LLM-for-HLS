<<<<<<< HEAD
#pragma ACCEL kernel
=======
Code: #pragma ACCEL kernel
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
<<<<<<< HEAD
  int k;
  int idx;
  int idx0;
  int idx1;
  int idx2;
  int idx3;
  int idx4;
  int idx5;
  int idx6;
  int idx7;
  int idx8;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    middle:
    for (j = 0; j < 8; j++) {
      idx0 = i * 8 + j;
      idx = idx0 * 8;
      val = orig[idx0] + filter[0] * (orig[idx0 - 8] + orig[idx0 + 8]) + filter[1] * (orig[idx0 - 7] + orig[idx0 + 7]) + filter[2] * (orig[idx0 - 6] + orig[idx0 + 6]) + filter[3] * (orig[idx0 - 5] + orig[idx0 + 5]) + filter[4] * (orig[idx0 - 4] + orig[idx0 + 4]) + filter[5] * (orig[idx0 - 3] + orig[idx0 + 3]) + filter[6] * (orig[idx0 - 2] + orig[idx0 + 2]) + filter[7] * (orig[idx0 - 1] + orig[idx0 + 1]);
      sol[idx0] = val;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 1; k < 8; k++) {
        idx = idx0 * 8 + k;
        val = orig[idx] + filter[0] * (sol[idx - 8] + sol[idx + 8]) + filter[1] * (sol[idx - 7] + sol[idx + 7]) + filter[2] * (sol[idx - 6] + sol[idx + 6]) + filter[3] * (sol[idx - 5] + sol[idx + 5]) + filter[4] * (sol[idx - 4] + sol[idx + 4]) + filter[5] * (sol[idx - 3] + sol[idx + 3]) + filter[6] * (sol[idx - 2] + sol[idx + 2]) + filter[7] * (sol[idx - 1] + sol[idx + 1]);
        sol[idx] = val;
      }
=======
  int t;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_up;
  int col_down;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_stencil_1:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_stencil_2:
    for (j = 0; j < 8; j++) {
      row = i * 8;
      row_up = (i - 1) * 8;
      row_down = (i + 1) * 8;
      col = j * 8;
      col_up = (j - 1) * 8;
      col_down = (j + 1) * 8;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      loop_stencil_3:
      for (k = 0; k < 9; k++) {
        t += filter[k] * orig[row + (_off_up_down[k] + 0)[row_up,row,row_down] + (_off_left_right[k] + 0)[col_up,col,col_down]];
      }
      sol[row + col] = t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}