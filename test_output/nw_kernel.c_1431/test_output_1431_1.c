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
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    M[a_idx] = a_idx;
    ptr[a_idx] = - 1;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx;
    ptr[b_idx * 5] = - 1;
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  loop_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    loop_col:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      score = ((SEQA[a_idx] == SEQB[b_idx]) ? 1 : (- 1));
      row_up = a_idx * 5;
      up_left = score + M[row_up + b_idx];
      up = M[row_up + b_idx + 1] + 1;
      left = M[row_up + b_idx + 1] + 1;
      max = (up_left > ((up > left) ? up : left)) ? up_left : ((up > left) ? up : left);
      M[a_idx * 5 + b_idx] = max;
      row = a_idx * 5 + b_idx;
      if (max == left) {
        ptr[row] = ((b_idx == 0) ? (- 1) : (row - 1));
      }
      
#pragma ACCEL PIPELINE auto{off}
      if (max == up) {
        ptr[row] = row_up;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      if (max == up_left) {
        ptr[row] = (b_idx == 0) ? (- 1) : (ptr[row - 1] + 1);
      }
    }
  }
// TraceBack
  a_idx = 4;
  b_idx = 4;
  a_str_idx = 0;
  b_str_idx = 0;
/*
    row_up = a_idx * 5;
    r = M[row_up + b_idx];
    while (a_idx > 0 || b_idx > 0) {
      row_up = a_idx * 5;
      if (r == M[row_up + b_idx]) {
        a_idx--;
        b_idx--;
        a_str_idx++;
        b_str_idx++;
        r = M[row_up + b_idx];
      }
      else {
        max = 0;
        row = row_up;
        if (M[row + b_idx] > max) {
          max = M[row + b_idx];
          ptr[row + b_idx] = - 1;
        }
        row = row_up + 1;
        if (M[row + b_idx] > max) {
          max = M[row + b_idx];
          ptr[row + b_idx] = row_up;
        }
        row = row_up + 5;
        if (M[row + b_idx] > max) {
          max = M[row + b_idx];
          ptr[row + b_idx] = row_up + 1;
        }
        a_idx = ptr[row + b_idx];
        b_idx = b_idx + 1;
        a_str_idx++;
        b_str_idx++;
        r = M[row_up + b_idx];
      }
    }
*/
  while (1) {
    row_up = a_idx * 5;
    if (a_idx == 0 && b_idx == 0) {
      break;
    }
    if (b_idx == 0) {
      a_idx--;
      b_idx++;
      a_str_idx++;
      b_str_idx++;
    }
    else if (a_idx == 0) {
      b_idx--;
      a_str_idx++;
      b_str_idx++;
    }
    else {
      r = M[row_up + b_idx] + ((SEQA[a_idx] == SEQB[b_idx]) ? 1 : (- 1));
      up = M[row_up + b_idx + 1] + 1;
      left = M[row_up + b_idx - 1] + 1;
      if (up < left) {
        if (up < r) {
          a_idx--;
          b_str_idx++;
        }
        else {
          a_idx--;
          b_idx++;
          a_str_idx++;
          b_str_idx++;
        }
      }
      else {
        if (left < r) {
          b_idx--;
          a_str_idx++;
          b_str_idx++;
        }
        else {
          a_idx--;
          b_idx++;
          a_str_idx++;
          b_str_idx++;
        }
      }
    }
  }
/*
    a_idx = 4;
    b_idx = 4;
    a_str_idx = 0;
    b_str_idx = 0;
    row_up = a_idx * 5;
    r = M[row_up + b_idx];
    while (a_idx > 0 || b_idx > 0) {
      row_up = a_idx * 5;
      if (r == M[row_up + b_idx]) {
        a_idx--;
        b_idx--;
        a_str_idx++;
        b_str_idx++;
        r = M[row_up + b_idx];
      }
      else {
        max = 0;
        row = row_up;
        if (M[row + b_idx] > max) {
          max = M[row + b_idx];
          ptr[row + b_idx] = - 1;
        }
        row = row_up + 1;
        if (M[row + b_idx] > max) {
          max = M[row + b_idx];
          ptr[row + b_idx] = row_up;
        }
        row = row_up + 5;
        if (M[row + b_idx] > max) {
          max = M[row + b_idx];
          ptr[row + b_idx] = row_up + 1;
        }
        a_idx = ptr[row + b_idx];
        b_idx = b_idx + 1;
        a_str_idx++;
        b_str_idx++;