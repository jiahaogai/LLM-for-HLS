#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[160],char alignedB[160],int M[160][160])
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
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    M[a_idx][0] = a_idx * (-1);
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[0][b_idx] = b_idx * (-1);
  }
// Matrix score updating
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  fill_out:
  for (b_idx = 1; b_idx < 5; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    fill_in:
    for (a_idx = 1; a_idx < 5; a_idx++) {
      if (((int )SEQA[a_idx - 1]) == ((int )SEQB[b_idx - 1])) {
        score = 1;
      }
       else {
        score = -1;
      }
      row_up = 1 + a_idx - 1;
      row = 1 + a_idx;
      up_left = M[row_up][b_idx - 1] + score;
      up = M[row_up][b_idx] - 1;
      left = M[row][b_idx - 1] - 1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[row][b_idx] = max;
      if (max == left) {
        a_str_idx = (a_idx - 1);
        b_str_idx = (b_idx - 1);
      }
       else {
        if (max == up) {
          a_str_idx = a_idx - 1;
          b_str_idx = b_idx;
        }
         else {
          a_str_idx = a_idx;
          b_str_idx = b_idx - 1;
        }
      }
    }
  }
// TraceBack
  r = 5 - 1;
  a_idx = 5 - 1;
  b_idx = 5 - 1;
  a_str_idx = a_idx;
  b_str_idx = b_idx;
/*
    traceBack: while(a_idx!=0 || b_idx!=0) {
      if (b_idx == 0) {
        a_idx--;
        b_idx = a_idx;
      }
      else if (a_idx == 0) {
        b_idx--;
        a_idx = b_idx;
      }
      else if (M[a_idx - 1][b_idx - 1] > ((M[a_idx - 1][b_idx] + (-1)) + (M[a_idx][b_idx - 1] + (-1)))) {
        if (M[a_idx - 1][b_idx] > M[a_idx][b_idx - 1]) {
          b_idx = b_idx - 1;
          a_idx = a_idx - 1;
        }
        else {
          b_idx = b_idx - 1;
        }
      }
      else if (M[a_idx - 1][b_idx - 1] < ((M[a_idx - 1][b_idx] + (-1)) + (M[a_idx][b_idx - 1] + (-1)))) {
        if (M[a_idx][b_idx - 1] > M[a_idx - 1][b_idx]) {
          a_idx = a_idx - 1;
          b_idx = b_idx - 1;
        }
        else {
          a_idx = a_idx - 1;
        }
      }
      else if (M[a_idx - 1][b_idx - 1] == ((M[a_idx - 1][b_idx] + (-1)) + (M[a_idx][b_idx - 1] + (-1)))) {
        b_idx = b_idx - 1;
        a_idx = a_idx - 1;
      }
    }
*/
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  trace: while(a_idx != 0 || b_idx != 0) {
    if (b_idx == 0) {
      a_idx--;
      b_idx = a_idx;
    }
     else if (a_idx == 0) {
      b_idx--;
      a_idx = b_idx;
    }
     else if (M[a_idx - 1][b_idx - 1] > ((M[a_idx - 1][b_idx] + (-1)) + (M[a_idx][b_idx - 1] + (-1)))) {
      if (M[a_idx - 1][b_idx] > M[a_idx][b_idx - 1]) {
        b_idx = b_idx - 1;
        a_idx = a_idx - 1;
      }
      else {
        b_idx = b_idx - 1;
      }
    }
     else if (M[a_idx - 1][b_idx - 1] < ((M[a_idx - 1][b_idx] + (-1)) + (M[a_idx][b_idx - 1] + (-1)))) {
      if (M[a_idx][b_idx - 1] > M[a_idx - 1][b_idx]) {
        a_idx = a_idx - 1;
        b_idx = b_idx - 1;
      }
      else {
        a_idx = a_idx - 1;
      }
    }
     else if (M[a_idx - 1][b_idx - 1] == ((M[a_idx - 1][b_idx] + (-1)) + (M[a_idx][b_idx - 1] + (-1)))) {
      b_idx = b_idx - 1;
      a_idx = a_idx - 1;
    }
  }
// Alignment
// Pad A
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  pad_a: for (a_idx = 0; a_idx < 160; a_idx++) {
    alignedA[a_idx] = (char )0;
  }
// Pad B
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  pad_b: for (b_idx = 0; b_idx < 160; b_idx++) {
    alignedB[b_idx] = (char )0;
  }
// Write A
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1