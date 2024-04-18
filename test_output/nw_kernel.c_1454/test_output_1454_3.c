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
  int a_str_idx;
  int b_str_idx;
  int a_str_idx_p1;
  int b_str_idx_p1;
  char a;
  char b;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    M[a_idx] = a_idx;
    ptr[a_idx] = -1;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx;
    ptr[b_idx * 5] = -1;
  }
/* The score of aligning empty string is 0.  */
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  loop_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L3_0}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3_0}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3_0}
    loop_col:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      a_str_idx = 5 * a_idx;
      b_str_idx = 5 * b_idx;
      a_str_idx_p1 = a_str_idx + 1;
      b_str_idx_p1 = b_str_idx + 1;
      if (a_idx == 0) {
        score = b_idx;
      }
      else if (b_idx == 0) {
        score = a_idx;
      }
      else {
        up_left = M[a_str_idx_p1 + b_str_idx] + ((int )SEQA[a_str_idx] == (int )SEQB[b_str_idx] ? 1 : (-1));
        up = M[a_str_idx_p1 + b_str_idx_p1] + ((int )SEQA[a_str_idx] == (int )SEQB[b_str_idx_p1] ? 1 : (-1));
        left = M[a_str_idx + b_str_idx_p1] + ((int )SEQA[a_str_idx_p1] == (int )SEQB[b_str_idx] ? 1 : (-1));
        max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
        score = max;
        row_up = a_str_idx_p1 + b_idx;
        r = a_idx - 1;
      }
      M[b_str_idx + a_idx] = score;
      if (score == left) {
        ptr[b_str_idx + a_idx] = b_str_idx_p1;
      }
      else {
        if (score == up) {
          ptr[b_str_idx + a_idx] = b_str_idx;
        }
        else {
          ptr[b_str_idx + a_idx] = row_up;
        }
      }
    }
  }
  row = 5 - 1;
  b_idx = 5 - 1;
  a_str_idx = (5 - 1) * 5;
  b_str_idx = (5 - 1) * 5;
/* Follow the trace back starting from the right bottom cell */
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
  trace_back:
  while (b_idx != 0 || a_idx != 0) {
    if (b_idx == 0) {
      a_idx = row;
      b_idx = b_str_idx + 1;
      a_str_idx = b_str_idx;
      b_str_idx = ptr[b_str_idx];
    }
    else {
      if (a_idx == 0) {
        b_idx = b_str_idx;
        a_idx = a_str_idx;
        b_str_idx = ptr[b_str_idx];
      }
      else {
        if (M[a_str_idx + b_str_idx] > M[a_str_idx + b_str_idx + 1] && M[a_str_idx + b_str_idx] > M[a_str_idx + 1 + b_str_idx]) {
          a_idx = a_str_idx;
          b_idx = b_str_idx;
        }
        else {
          if (M[a_str_idx + 1 + b_str_idx] > M[a_str_idx + b_str_idx] && M[a_str_idx + 1 + b_str_idx] > M[a_str_idx + 1 + b_str_idx]) {
            a_idx = a_str_idx + 1;
            b_idx = b_str_idx + 1;
          }
          else {
            a_idx = a_str_idx + 1;
            b_idx = b_str_idx;
          }
        }
        a_str_idx = a_str_idx + 1;
        b_str_idx = ptr[b_str_idx];
      }
    }
    alignedA[a_idx] = SEQA[a_idx];
    alignedB[b_idx] = SEQB[b_idx];
  }
  alignedA[a_idx] = SEQA[a_idx];
  alignedB[b_idx] = SEQB[b_idx];
}