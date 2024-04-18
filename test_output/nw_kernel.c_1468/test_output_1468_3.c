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
  int idx_row;
  int idx_row_up;
  int label;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx * 24] = '-';
    alignedA[a_idx * 24 + 24] = '\0';
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx * 24] = '-';
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  fill_out:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    fill_in:
    for (a_idx = 0; a_idx < 5; a_idx++) {
      if (((int )SEQA[a_idx]) == ((int )SEQB[b_idx])) {
        score = 1;
      }
       else {
        score = -1;
      }
      if (a_idx == 0 || b_idx == 0) {
        if (a_idx == 0 && b_idx == 0) {
          M[0] = 0;
        }
         else if (a_idx == 0) {
          M[b_idx * 5] = - 1 * b_idx;
        }
         else {
          M[b_idx * 5] = - 1 * a_idx;
        }
      }
       else {
        up_left = M[(b_idx - 1) * 5 + (a_idx - 1)] + score;
        up = M[(b_idx - 1) * 5 + a_idx] - 1;
        left = M[b_idx * 5 + (a_idx - 1)] - 1;
        M[b_idx * 5 + a_idx] = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
        if (M[b_idx * 5 + a_idx] > ((int )0)) {
          label = ((b_idx - 1) * 5 + (a_idx - 1));
        }
         else {
          label = ((b_idx - 1) * 5 + a_idx);
        }
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  row = 24;
  row_up = 29;
  a_idx = 4;
  b_idx = 4;
  a_str_idx = 116;
  b_str_idx = 116;
  idx_row = b_idx * 5;
  idx_row_up = (b_idx - 1) * 5;
  trace: while(a_idx != 0 || b_idx != 0) {
//#A = str[a_idx - 1]
//#B = str[b_idx - 1]
    if (M[idx_row + a_idx] == - 1 * b_idx) {
      a_idx--;
      b_idx--;
      a_str_idx -= 2;
      b_str_idx -= 2;
      alignedA[a_str_idx] = SEQA[a_idx];
      alignedA[a_str_idx + 1] = '_';
      alignedB[b_str_idx] = '_';
      alignedB[b_str_idx + 1] = SEQB[b_idx];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    trace_row:
    for (r = 0; r < 5; r++) {
      left = M[idx_row + (a_idx - 1)];
      up = M[idx_row_up + a_idx];
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      if (max == left) {
        a_idx--;
        b_str_idx -= 2;
        alignedA[a_str_idx] = SEQA[a_idx];
        alignedA[a_str_idx + 1] = '_';
        alignedB[b_str_idx] = '_';
        alignedB[b_str_idx + 1] = SEQB[b_idx];
      }
       else {
        if (max == up) {
          b_idx--;
          a_str_idx -= 2;
          alignedA[a_str_idx] = '_';
          alignedA[a_str_idx + 1] = SEQA[a_idx];
          alignedB[b_str_idx] = SEQB[b_idx];
          alignedB[b_str_idx + 1] = '_';
        }
         else {
          a_idx--;
          b_idx--;
          a_str_idx -= 2;
          b_str_idx -= 2;
          alignedA[a_str_idx] = SEQA[a_idx];
          alignedA[a_str_idx + 1] = '_';
          alignedB[b_str_idx] = '_';
          alignedB[b_str_idx + 1] = SEQB[b_idx];
        }
      }
    }
    idx_row = idx_row_up;
    idx_row_up = (b_idx - 1) * 5;
  }
}