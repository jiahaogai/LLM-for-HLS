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
  int score_row;
  int u;
  int _in_x;
  int _in_y;
  int _out_y;
  int _out_x;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_idx = 0; a_idx < 128 + 1; a_idx++) {
    M[a_idx] = a_idx * - 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 128 + 1; b_idx++) {
    M[b_idx * (128 + 1)] = b_idx * - 1;
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  fill_out:
  for (b_idx = 1; b_idx < 128 + 1; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    fill_in:
    for (a_idx = 1; a_idx < 128 + 1; a_idx++) {
      if (((int )SEQA[a_idx - 1]) == ((int )SEQB[b_idx - 1])) {
        score = 1;
      }
       else {
        score = - 1;
      }
      row_up = (b_idx - 1) * (128 + 1);
      up_left = M[row_up + (a_idx - 1)] + score;
      up = M[row_up + a_idx] + - 1;
      left = M[b_idx * (128 + 1) + (a_idx - 1)] + - 1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[b_idx * (128 + 1) + a_idx] = max;
      if (max == left) {
        ptr[b_idx * (128 + 1) + a_idx] = 2;
      }
       else {
        if (max == up) {
          ptr[b_idx * (128 + 1) + a_idx] = 1;
        }
         else {
          ptr[b_idx * (128 + 1) + a_idx] = 0;
        }
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  score = M[(128 + 1) * (128 + 1) - 1];
  a_idx = ((128 + 1) - 1);
  b_idx = ((128 + 1) - 1);
  a_str_idx = 0;
  b_str_idx = 0;
  score_row = 0;
// Row traceBack
  
#pragma ACCEL PIPELINE auto{__PIPE__L4}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
  trace_row:
  while (a_idx > 0) {
// Column traceBack
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
    trace_col:
    while (b_idx > 0) {
      u = ptr[b_idx * (128 + 1) + a_idx];
      if (u == 0) {
        a_idx--;
        b_idx--;
        alignedA[a_str_idx++] = SEQA[a_idx];
        alignedB[b_str_idx++] = SEQB[b_idx];
        score_row += 1;
      }
       else {
        if (u == 1) {
          b_idx--;
          alignedA[a_str_idx++] = SEQA[a_idx];
          alignedB[b_str_idx++] = SEQB[b_idx];
        }
         else {
          a_idx--;
          alignedA[a_str_idx++] = SEQA[a_idx];
          alignedB[b_str_idx++] = SEQB[b_idx];
        }
      }
    }
    b_idx = ((128 + 1) - 1);
    row = b_idx * (128 + 1);
  }
}