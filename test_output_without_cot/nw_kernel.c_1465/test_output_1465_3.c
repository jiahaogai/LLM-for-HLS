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
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  init_row:
  for (a_idx = 0; a_idx < 128 + 1; a_idx++) {
    M[a_idx] = a_idx * - 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_col:
  for (b_idx = 0; b_idx < 128 + 1; b_idx++) {
    M[b_idx * (128 + 1)] = b_idx * - 1;
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  fill_out:
  for (b_idx = 1; b_idx < 128 + 1; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    fill_in:
    for (a_idx = 1; a_idx < 128 + 1; a_idx++) {
      if (((int )SEQA[a_idx - 1]) == ((int )SEQB[b_idx - 1])) {
        score = 1;
      }
       else {
        score = - 1;
      }
      row_up = (b_idx - 1) * (128 + 1);
      row = b_idx * (128 + 1);
      up_left = M[row_up + (a_idx - 1)] + score;
      up = M[row_up + a_idx] + - 1;
      left = M[row + (a_idx - 1)] + - 1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[row + a_idx] = max;
      if (max == left) {
        ptr[row + a_idx] = ((char )60);
      }
       else {
        if (max == up) {
          ptr[row + a_idx] = ((char )94);
        }
         else {
          ptr[row + a_idx] = ((char )92);
        }
      }
    }
  }
// Traceback
  a_idx = 128;
  b_idx = 128;
  a_str_idx = 0;
  b_str_idx = 0;
/*
    fprintf(stderr, "@%d,%d\n", a_idx, b_idx);
*/
  
#pragma ACCEL PIPELINE auto{off}
  trace:
  while (a_idx != 0 || b_idx != 0) {
    r = b_idx * (128 + 1);
    if (ptr[r + a_idx] == 60) {
      a_idx--;
      b_idx--;
      alignedA[a_str_idx++] = SEQA[a_idx];
      alignedB[b_str_idx++] = SEQB[b_idx];
    }
     else {
      if (ptr[r + a_idx] == 94) {
        a_idx--;
        alignedA[a_str_idx++] = SEQA[a_idx];
        alignedB[b_str_idx++] = '-';
      }
       else {
        b_idx--;
        alignedA[a_str_idx++] = '-';
        alignedB[b_str_idx++] = SEQB[b_idx];
      }
    }
/*
    fprintf(stderr, "@%d,%d\n", a_idx, b_idx);
*/
  }
}