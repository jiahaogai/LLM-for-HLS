<<<<<<< HEAD
Code: #pragma ACCEL kernel
=======
#pragma ACCEL kernel
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int tmp;
=======
  int sum;
  int row;
  int col;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
<<<<<<< HEAD
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
=======
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PIPELINE auto{off}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
<<<<<<< HEAD
    for (j = 1; j < 8190; j++) {
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        tmp += orig[i + row[k] - 1] [j + col[k] - 1] * filter[k];
      }
      sol[i - 1] [j - 1] = tmp;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:30:35: error: ‘align’ undeclared (first use in this function)
   30 |         tmp += orig[i * 256 + j + align[k]] * filter[k];
      |                                   ^~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:30:35: note: each undeclared identifier is reported only once for each function it appears in

Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int orig_row_start;
  int orig_row_end;
  int orig_col_start;
  int orig_col_end;
  int sol_row_start;
  int sol_row_end;
  int sol_col_start;
  int sol_col_end;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  orig_row_start = 1;
  orig_row_end = 8190;
  orig_col_start = 1;
  orig_col_end = 8190;
  sol_row_start = 1;
  sol_row_end = 8190;
  sol_col_start = 1;
  sol_col_end = 8190;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_row:
  for (i = orig_row_start; i < orig_row_end + 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_col:
    for (j = orig_col_start; j < orig_col_end + 1; j++) {
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      loop_k:
      for (k = 0; k < 9;
=======
    for (j = 1; j < 8191; j++) {
      sum = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        row = i + (-1 + k);
        col = j + (-1 + k);
        if (row < 1 || row > 8191) {
          row = 1;
        }
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        if (col < 1 || col > 8191) {
          col = 1;
        }
        sum += orig[row * 8192 + col] * filter[k];
      }
      sol[i * 8192 + j] = sum;
    }
  }
}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
