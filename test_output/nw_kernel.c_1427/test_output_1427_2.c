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
  int max_row;
  int max_row_up;
  int i;
  int j;
  int A_len_min_B_len;
//#pragma scop
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  a_str_idx = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  b_str_idx = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  A_len_min_B_len = ((SEQA[0] == SEQB[0]) ? 1 : 0);
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  score = 0;
  row = 0;
  r = 0;
  while (a_str_idx < 128) {
    b_idx = 0;
    row_up = ((a_str_idx == 0) ? 0 : row);
    while (b_str_idx < 128) {
      a_idx = a_str_idx;
      up_left = M[row * 128 + a_idx];
      up = M[row_up * 128 + a_idx];
      if (b_str_idx == 0) {
        left = 0;
      }
      else {
        left = M[row * 128 + (b_str_idx - 1)];
      }
      max_row_up = (up_left > up ? (up_left > left ? 0 : 2) : (up > left ? 1 : 2));
      max_row = M[row * 128 + b_str_idx];
      max = (max_row > max_row_up ? max_row : max_row_up);
      if (a_idx == 0) {
        score = max;
      }
      else {
        score = (max + 1);
      }
      if (a_idx >= b_idx) {
        M[row * 128 + b_idx] = score;
        ptr[row * 128 + b_idx] = 3;
      }
      else {
        M[row * 128 + b_idx] = score;
        ptr[row * 128 + b_idx] = 2;
      }
      if (max_row_up == left) {
        b_idx++;
      }
      else {
        if (max_row_up == up) {
          a_idx++;
          b_idx = b_str_idx;
          row_up = row;
          row++;
        }
        else {
          a_idx++;
          b_str_idx++;
        }
      }
    }
    b_str_idx = A_len_min_B_len + 1;
    r++;
    a_str_idx++;
  }
  i = 0;
  j = 0;
  a_idx = 127;
  b_idx = 127;
  score_row = 127 * 128;
  while (i < 128) {
    j = 0;
    while (j < 128) {
      if (ptr[score_row + j] == 3) {
        alignedA[i * 128 + j] = SEQA[a_idx];
        alignedB[i * 128 + j] = SEQB[b_idx];
        a_idx--;
        b_idx--;
      }
      else {
        if (ptr[score_row + j] == 2) {
          alignedA[i * 128 + j] = SEQA[a_idx];
          alignedB[i * 128 + j] = '-';
          a_idx--;
        }
        else {
          alignedA[i * 128 + j] = '-';
          alignedB[i * 128 + j] = SEQB[b_idx];
          b_idx--;
        }
      }
      j++;
    }
    score_row += 128;
    j = 127;
    i++;
  }
//#pragma endscop
}