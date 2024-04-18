c
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
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    M[a_idx] = a_idx;
    alignedA[a_idx] = '-';
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx;
    alignedB[b_idx] = '-';
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    fill_b:
    for (a_idx = 1; a_idx < 5; a_idx++) {
      a_str_idx = 5 * a_idx;
      b_str_idx = 5 * b_idx;
      a_str_idx_p1 = a_str_idx + 1;
      b_str_idx_p1 = b_str_idx + 1;
      a = (char )SEQA[a_str_idx_p1];
      b = (char )SEQB[b_str_idx_p1];
      score = ((int )a == ((int )b) ? 1 : -1);
      up_left = M[b_str_idx * 5 + (a_idx - 1)] + score;
      up = M[b_str_idx * 5 + a_idx] - 1;
      left = M[a_str_idx_p1 + b_idx] - 1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[b_str_idx * 5 + a_idx] = max;
      row_up = b_str_idx * 5 + (a_idx - 1);
      if (max == left) {
        ptr[row_up] = ((char )60);
        alignedA[a_str_idx_p1] = '-';
      }
      
      if (max == up) {
        ptr[row_up] = ((char )94);
        alignedA[a_str_idx_p1] = a;
      }
      
      if (max == up_left) {
        ptr[row_up] = b_str_idx_p1;
        alignedA[a_str_idx_p1] = a;
      }
    }
  }
  row = (5 * 5) - 1;
  a_idx = 5 - 1;
  b_idx = 5 - 1;
  a_str_idx = (5 * 5) - 1;
  b_str_idx = (5 * 5) - 1;
/*
    traceback:
    while (a_idx != 0 || b_idx != 0) {
      if (b_idx == 0) {
        a_idx--;
        a_str_idx -= 5;
        b_idx = 5;
      }
      else if (a_idx == 0) {
        b_idx--;
        b_str_idx -= 5;
        a_idx = 5;
      }
      else if (M[b_str_idx * 5 + a_idx] == (M[b_str_idx * 5 + (a_idx - 1)] + (- 1))) {
        a_idx--;
        a_str_idx -= 5;
        b_idx = 5 * b_idx + a_idx;
      }
      else if (M[b_str_idx * 5 + a_idx] == (M[(b_str_idx - 1) * 5 + a_idx] + (- 1))) {
        b_idx--;
        b_str_idx -= 5;
        a_idx = 5 * b_idx + a_idx;
      }
      else if (M[b_str_idx * 5 + a_idx] == (M[b_str_idx * 5 + (a_idx - 1)] + 1)) {
        a_idx--;
        a_str_idx -= 5;
        b_idx = 5 * b_idx + a_idx;
        alignedA[a_str_idx + 1] = a;
      }
      else if (M[b_str_idx * 5 + a_idx] == (M[(b_str_idx - 1) * 5 + a_idx] + 1)) {
        b_idx--;
        b_str_idx -= 5;
        a_idx = 5 * b_idx + a_idx;
        alignedA[a_str_idx + 1] = a;
        alignedB[b_str_idx + 1] = b;
      }
      else if (M[b_str_idx * 5 + a_idx] == (M[b_str_idx * 5 + (a_idx - 1)] + 1)) {
        a_idx--;
        a_str_idx -= 5;
        b_idx = 5 * b_idx + a_idx;
        alignedA[a_str_idx + 1] = a;
        alignedB[b_str_idx + 1] = b;
      }
    }
    alignedA[0] = '\0';
    alignedB[0] = '\0';
  }