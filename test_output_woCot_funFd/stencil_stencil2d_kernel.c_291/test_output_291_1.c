<<<<<<< HEAD
Code: #pragma ACCEL kernel

void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
=======
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
{
  int i;
  int j;
  int k;
  int idx;
<<<<<<< HEAD
  int fidx;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_up;
  int col_down;
=======
  int center = 4;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  loop_row:
  for (row = 1; row < 64 + 1 - 1; row++) {
=======
  outer:
  for (i = 1; i < 64 - 1; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
<<<<<<< HEAD
    loop_col:
    for (col = 1; col < 128 + 1 - 1; col++) {
      idx = (row - 1) * 128 + col - 1;
      row_up = row - 1;
      row_down = row + 1;
      col_up = col - 1;
      col_down = col + 1;
      if (row_up == 0) {
        row_up = 1;
      }
      if (col_up == 0) {
        col_up = 1;
      }
      if (row_down == 64 + 1 - 1) {
        row_down = 64;
      }
      if (col_down == 128 + 1 - 1) {
        col_down = 128;
      }
      loop_fidx:
      for (fidx = 0; fidx < 9; fidx++) {
        sol[idx] += filter[fidx] * orig[row_up * 128 + col_up - 1];
      }
      loop_fidx:
      for (fidx = 0; fidx < 9; fidx++) {
        sol[idx] += filter[fidx] * orig[row_up * 128 + col_down - 1];
      }
      loop_fidx:
      for (fidx = 0; fidx < 9; fidx++) {
        sol[idx] += filter[fidx] * orig[row_down * 128 + col_up - 1];
      }
      loop_fidx:
      for (fidx = 0; fidx < 9; fidx++) {
        sol[idx] += filter[fidx] * orig[row_down * 128 + col_down - 1];
      }
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘kernel_stencil’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:53:7: error: duplicate label ‘loop_fidx’
   53 |       loop_fidx:
      |       ^~~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:49:7: note: previous definition of ‘loop_fidx’ was here
   49 |       loop_fidx:
      |       ^~~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:57:7: error: duplicate label ‘loop_fidx’
   57 |       loop_fidx:
      |       ^~~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:49:7: note: previous definition of ‘loop_fidx’ was here
   49 |       loop_fidx:
      |       ^~~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:61:7: error: duplicate label ‘loop_fidx’
   61 |
=======
    inner:
    for (j = 1; j < 128 - 1; j++) {
      idx = i * 128 + j;
      sol[idx] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      filter_idx:
      for (k = 0; k < 9; k++) {
        int cur_filter;
        int cur_idx;
        cur_filter = filter[k];
        cur_idx = idx + ((center - k) * 128);
        sol[idx] += cur_filter * orig[cur_idx];
      }
    }
  }
}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
