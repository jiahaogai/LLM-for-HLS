#pragma ACCEL kernel

void needwun(int ALIGN,char SEQA[128],char SEQB[128],int M[16641],int E[16641],int PTR[16641],char alignedA[16641],char alignedB[16641])
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
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    M[a_idx] = a_idx;
    E[a_idx] = 0;
    PTR[a_idx] = 0;
    alignedA[a_idx] = '-';
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx;
    E[b_idx * 5] = 0;
    PTR[b_idx * 5] = 0;
    alignedB[b_idx] = '-';
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  fill_out:
  for (b_idx = 1; b_idx < 5; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    fill_in:
    for (a_idx = 1; a_idx < 5; a_idx++) {
      if (((int )SEQA[a_idx - 1]) == ((int )SEQB[b_idx - 1])) {
        score = 1;
      }
       else {
        score = -1;
      }
      row_up = (b_idx - 1) * 5;
      row = b_idx * 5;
      a_str_idx = a_idx - 1;
      b_str_idx = b_idx - 1;
      up_left = M[row_up + a_str_idx] + score;
      up = M[row_up + a_idx] - 1;
      left = M[row + a_str_idx] - 1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[row + a_idx] = max;
      if (max == left) {
        E[row + a_idx] = 2;
        PTR[row + a_idx] = a_str_idx;
      }
       else {
        if (max == up) {
          E[row + a_idx] = 1;
          PTR[row + a_idx] = row_up + a_idx;
        }
         else {
          E[row + a_idx] = 3;
          PTR[row + a_idx] = (row_up + a_str_idx);
        }
      }
      if (max == left) {
        alignedA[a_idx] = SEQA[a_str_idx];
        alignedB[b_idx] = '-';
      }
       else {
        if (max == up) {
          alignedA[a_idx] = '-';
          alignedB[b_idx] = SEQB[b_str_idx];
        }
         else {
          a_str_idx = PTR[row + a_idx];
          b_str_idx = PTR[row + a_idx] - 5;
          alignedA[a_idx] = SEQA[a_str_idx];
          alignedB[b_idx] = SEQB[b_str_idx];
        }
      }
    }
  }
// Trace-back operation
  r = 4 * 5;
  a_idx = 4;
  b_idx = 4;
  a_str_idx = a_idx;
  b_str_idx = b_idx;
/*
    trace_out:
    while (a_idx != 0 || b_idx != 0) {
      if (E[r] == 4) {
        a_str_idx = PTR[r];
        b_str_idx = r - a_str_idx;
        alignedA[a_idx] = SEQA[a_str_idx];
        alignedB[b_idx] = SEQB[b_str_idx];
        a_idx--;
        b_idx--;
        r = b_idx * 5 + a_idx;
      }
       else {
        if (E[r] == 3) {
          a_str_idx = PTR[r];
          b_str_idx = r - a_str_idx;
          alignedA[a_idx] = '-';
          alignedB[b_idx] = SEQB[b_str_idx];
          b_idx--;
          r = b_idx * 5 + a_idx;
        }
         else {
          if (E[r] == 2) {
            a_str_idx = PTR[r];
            b_str_idx = r - a_str_idx;
            alignedA[a_idx] = SEQA[a_str_idx];
            alignedB[b_idx] = '-';
            a_idx--;
            r = b_idx * 5 + a_idx;
          }
           else {
            if (E[r] == 1) {
              a_str_idx = PTR[r];
              b_str_idx = r - a_str_idx;
              alignedA[a_idx] = '-';
              alignedB[b_idx] = SEQB[b_str_idx];
              a_idx--;
              b_idx--;
              r = b_idx * 5 + a_idx;
            }
          }
        }
      }
    }
*/
}