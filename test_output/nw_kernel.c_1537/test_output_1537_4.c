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
  char a_char;
  char b_char;
  int idx;
  int next_idx;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
  }
  alignedA[5] = (char )'\0';
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  alignedB[5] = (char )'\0';
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  row_init:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    a_str_idx = (a_idx * 16) + 1;
    b_str_idx = 1;
    a_str_idx_p1 = a_str_idx + 1;
    b_str_idx_p1 = 1 + 1;
    a_char = (char )'\0';
    b_char = SEQA[a_str_idx];
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    init_diag:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      if (b_idx < a_idx) {
        score = -1;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L5}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
      diag_score:
      while (b_str_idx < b_idx + 1) {
        if (a_char == SEQB[b_str_idx]) {
          score = 1;
        }
        else {
          score = -1;
        }
        M[b_str_idx * 5L + a_idx] = ((up_left + score) > ((up + 0) ? (up + 0) : (up_left + score))) ? (up_left + score) : ((up + 0) ? (up + 0) : (up_left + score));
        ptr[b_str_idx * 5L + a_idx] = (char )'d';
        up_left = M[(b_str_idx + 1) * 5L + (a_idx + 1)] + ((a_char == SEQB[b_str_idx]) ? 1 : (-1));
        up = M[b_str_idx * 5L + a_idx + 1] + ((a_char == SEQB[b_str_idx]) ? 1 : (-1));
        left = M[b_str_idx * 5L + a_idx] + ((a_char == SEQB[b_str_idx]) ? 1 : (-1));
        max = (up_left > ((up + 0) ? (up + 0) : (up_left)));
        max = (max > ((left + 0) ? (left + 0) : (max)));
        a_char = b_char;
        b_char = SEQA[b_str_idx_p1 * 16L + a_str_idx_p1];
        b_str_idx = b_str_idx + 1;
        b_str_idx_p1 = b_str_idx_p1 + 1;
        a_str_idx = a_str_idx_p1;
        a_str_idx_p1 = a_str_idx_p1 + 1;
      }
    }
  }
  row = 5;
  b_idx = 5;
  a_idx = row - 1;
  a_str_idx = (a_idx * 16) + 1;
  b_str_idx = b_idx + 1;
  a_str_idx_p1 = a_str_idx + 1;
  b_str_idx_p1 = b_str_idx + 1;
  a_char = (char )'\0';
  b_char = SEQA[a_str_idx];
  idx = b_idx * 5L;
  next_idx = (b_idx + 1) * 5L;
  
#pragma ACCEL PIPELINE auto{__PIPE__L7}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
  traceback:
  while (a_idx > 0) {
    up_left = M[b_str_idx * 5L + a_idx] + ((a_char == SEQB[b_str_idx]) ? 1 : (-1));
    up = M[b_str_idx * 5L + a_idx + 1] + ((a_char == SEQB[b_str_idx]) ? 1 : (-1));
    left = M[b_str_idx * 5L + a_idx] + ((a_char == SEQB[b_str_idx]) ? 1 : (-1));
    max = (up_left > ((up + 0) ? (up + 0) : (up_left)));
    max = (max > ((left + 0) ? (left + 0) : (max)));
    if (max == 0) {
      max = left;
      ptr[idx + a_idx] = (char )'l';
    }
    
#pragma ACCEL IF(max)
    if (max == left) {
      a_char = b_char;
      b_char = SEQA[b_str_idx_p1 * 16L + a_str_idx_p1];
      b_str_idx = b_str_idx_p1;
      b_str_idx_p1 = b_str_idx_p1 + 1;
      a_str_idx = a_str_idx_p1;
      a_str_idx_p1 = a_str_idx_p1 + 1;
      a_idx = a_idx + 1;
    }
    
#pragma ACCEL ELSE
    if (max == up) {
      a_char = a_char;
      b_char = SEQB[b_str_idx_p1];
      b_str_idx = b_str_idx_p1;
      b_str_idx_p1 = b_str_idx_p1 + 1;
      a_str_idx = a_str_idx_p1;
      a_str_idx_p1 = a_str_idx_p1 + 1;
      a_idx = a_idx + 1;
    }
    
#pragma ACCEL ENDIF
  }
  a_char = b_char;
  b_char = SEQA[b_str_idx_p1 * 16L + a_str_idx_p1];