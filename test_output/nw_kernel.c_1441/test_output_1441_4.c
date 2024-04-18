#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[256],char alignedB[256],int M[16641],char ptr[16641])
{
  int score;
  int up_left;
  int up;
  int left;
  int max;
  int row;
  int row_up;
  int r;
  int a_idx;
  int b_idx;
  int a_idx_up;
  int b_idx_up;
  int a_idx_left;
  int b_idx_left;
  int a_row_end;
  int b_row_end;
  int a_col_end;
  int b_col_end;
  int a_ptr;
  int b_ptr;
  int index;
  int depth;
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    M[a_idx] = a_idx * - 1;
    ptr[a_idx] = - 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx * - 1;
    ptr[b_idx * 5] = - 1;
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  fill_out:
  for (b_idx = 1; b_idx < 5; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{128}
    fill_in:
    for (a_idx = 1; a_idx < 5; a_idx++) {
      if (((int )SEQA[a_idx - 1]) == ((int )SEQB[b_idx - 1])) {
        score = 1;
      }
       else {
        score = - 1;
      }
      row_up = (b_idx - 1) * 5;
      up_left = row_up + (a_idx - 1);
      up = row_up + a_idx;
      left = up_left;
      max = M[up_left] + score;
      row = up;
      if (M[up] > max) {
        max = M[up];
        row = up;
      }
      a_idx_up = a_idx - 1;
      b_idx_up = b_idx - 1;
      a_idx_left = a_idx - 1;
      b_idx_left = b_idx;
      if (((int )SEQA[a_idx_left]) == (- 1)) {
        a_idx_left = - 1;
      }
      if (((int )SEQB[b_idx_left]) == (- 1)) {
        b_idx_left = - 1;
      }
      a_row_end = a_idx_left * - 1 + 5;
      b_row_end = b_idx_left * - 1 + 5;
      a_col_end = a_idx_left * - 1;
      b_col_end = b_idx_left * - 1;
      if (a_row_end > row) {
        a_idx = a_row_end;
        b_idx = b_col_end;
      }
      else {
        if (b_row_end > row) {
          a_idx = a_col_end;
          b_idx = b_row_end;
        }
        else {
          M[row] = max;
          ptr[row] = ((b_idx == -1?- 1 : ((int )SEQB[b_idx])) * 5 + (a_idx == -1?- 1 : ((int )SEQA[a_idx])));
        }
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  a_idx = 4;
  b_idx = 4;
  index = 4 * 5 + 4;
  depth = 0;
  alignedA[depth] = ((int )'\000')?- 1 : ((int )SEQA[a_idx]);
  alignedB[depth] = ((int )'\000')?- 1 : ((int )SEQB[b_idx]);
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  traceback:
  while (((int )alignedA[0] != - 1) || ((int )alignedB[0] != - 1)) {
    a_idx = a_idx * - 1 + 5;
    b_idx = b_idx * - 1 + 5;
    index = b_idx + a_idx;
    depth++;
    alignedA[depth] = ((int )'\000')?- 1 : ((int )SEQA[a_idx]);
    alignedB[depth] = ((int )'\000')?- 1 : ((int )SEQB[b_idx]);
    a_ptr = ptr[index];
    b_ptr = a_ptr + 5;
    a_idx = a_ptr;
    b_idx = b_ptr;
  }
}