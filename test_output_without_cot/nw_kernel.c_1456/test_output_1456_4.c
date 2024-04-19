#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[160],char alignedB[160],int M[160][160],char ptr[160][160])
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
  int a_str_idx;
  int b_str_idx;
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_row:
  for (a_idx = 0; a_idx < 128 + 1; a_idx++) {
    M[a_idx][0] = a_idx * - 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  init_col:
  for (b_idx = 0; b_idx < 128 + 1; b_idx++) {
    M[0][b_idx] = b_idx * - 1;
  }
// Matrix filling.
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  fill_out:
  for (b_idx = 1; b_idx < 128 + 1; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
    fill_in:
    for (a_idx = 1; a_idx < 128 + 1; a_idx++) {
      if (((int )SEQA[a_idx - 1]) == ((int )SEQB[b_idx - 1])) {
        score = 1;
      }
       else {
        score = - 1;
      }
      up_left = M[a_idx - 1][b_idx - 1] + score;
      up = M[a_idx - 1][b_idx] - 1;
      left = M[a_idx][b_idx - 1] - 1;
      M[a_idx][b_idx] = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
/* Traceback. */
      
#pragma ACCEL PARA{__PARA__L2}
      if (M[a_idx][b_idx] == M[a_idx - 1][b_idx - 1] + score) {
        ptr[a_idx][b_idx] = 2;
        a_str_idx = a_idx - 1;
        b_str_idx = b_idx - 1;
      }
      
#pragma ACCEL PARA{__PARA__L3}
      else if (M[a_idx][b_idx] == up) {
        ptr[a_idx][b_idx] = 1;
        a_str_idx = a_idx - 1;
        b_str_idx = b_idx;
      }
      
#pragma ACCEL PARA{__PARA__L4}
      else {
        ptr[a_idx][b_idx] = 0;
        a_str_idx = a_idx;
        b_str_idx = b_idx - 1;
      }
    }
  }
// Trace back.
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L}
  trace:
  for (a_idx = 128; a_idx > 0; a_idx--) {
    row = 0;
    row_up = 1;
    b_idx = 128;
    b_str_idx = 128;
    trace_row:
    while (row < a_idx) {
      if (ptr[row + 1][b_idx] - ptr[row][b_idx] == 1) {
        up = 1;
      }
       else {
        up = 0;
      }
      if (ptr[row + 1][b_idx] - ptr[row][b_idx] == 0) {
        left = 1;
      }
       else {
        left = 0;
      }
      if (ptr[row + 1][b_idx] - ptr[row][b_idx] == 2) {
        max = M[row + 1][b_idx] + ((int )SEQA[row] == ((int )SEQB[b_str_idx]));
      }
       else {
        max = (M[row + 1][b_idx] > (M[row][b_idx] - 1))?M[row + 1][b_idx] : (M[row][b_idx] - 1);
      }
      if (max == M[row][b_idx] - ((int )SEQA[row] == ((int )SEQB[b_str_idx]))) {
        row_up = row;
        row = row + 1;
      }
       else {
        if (max == M[row + 1][b_idx] + ((int )SEQA[row] == ((int )SEQB[b_str_idx]))) {
          b_idx = b_str_idx;
        }
         else {
          b_idx = b_idx - 1;
        }
        row = row_up;
      }
      b_str_idx = b_idx;
    }
    trace_col:
    while (b_idx > 0) {
      if (ptr[a_idx][b_idx - 1] - ptr[a_idx][b_idx] == 1) {
        r = 1;
      }
       else {
        r = 0;
      }
      if (ptr[a_idx][b_idx - 1] - ptr[a_idx][b_idx] == 0) {
        a_str_idx = a_idx;
      }
       else {
        a_str_idx = a_idx - 1;
      }
      if (ptr[a_idx][b_idx - 1] - ptr[a_idx][b_idx] == 2) {
        max = M[a_idx][b_idx - 1] + ((int )SEQA[a_str_idx] == ((int )SEQB[b_idx - 1]));
      }
       else {
        max = (M[a_idx][b_idx - 1] > (M[a_idx][b_idx] - 1))?M[a_idx][b_idx - 1] : (M[a_idx][b_idx] - 1);
      }
      if (max == M[a_idx][b_idx] - ((int )SEQA[a_str_idx] == ((int )SEQB[b_idx - 1]))) {
        a_idx = a_str_idx;
      }
       else {
        if (max == M[a_idx][b_idx - 1] + ((int )SEQA[a_str_idx] == ((int )SEQB[b_idx - 1]))) {
          b_idx = b_idx - 1;
        }
         else {
          b_idx = b_idx + r;
        }
        a_idx = a_idx - 1;
      }
    }
  }
// Pad the result.
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
  pad_result:
  for (a_idx = 0; a_idx < 160; a_idx++) {
    alignedA[a_idx] = ((char )0);
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
  pad_result_b:
  for (b_