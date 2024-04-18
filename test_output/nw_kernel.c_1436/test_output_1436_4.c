#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[129],char alignedB[129],int M[16641],char ptr[16641])
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
  int index;
  int last_row_idx;
  int last_a_idx;
  int last_b_idx;
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_row:
  for (a_idx = 0; a_idx < 52; a_idx++) {
    M[a_idx] = a_idx * - 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 52; b_idx++) {
    M[b_idx * 52] = b_idx * - 1;
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  fill_in:
  for (b_idx = 1; b_idx < 52; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    fill_row:
    for (a_idx = 1; a_idx < 52; a_idx++) {
      if (((int )SEQA[a_idx - 1]) == ((int )SEQB[b_idx - 1])) {
        score = 1;
      }
       else {
        score = - 1;
      }
      row_up = (b_idx - 1) * 52;
      row = b_idx * 52;
      up_left = row_up + (a_idx - 1);
      up = row_up + a_idx;
      left = row + (a_idx - 1);
      max = ((int )M[up_left]) + score;
      if (max < ((int )M[up]) + - 1) {
        max = ((int )M[up]) + - 1;
      }
      if (max < ((int )M[left]) + - 1) {
        max = ((int )M[left]) + - 1;
      }
      M[row + a_idx] = max;
      ptr[row + a_idx] = 0;
      if (max == ((int )M[up_left]) + score) {
        ptr[row + a_idx] |= 4;
      }
      if (max == ((int )M[up]) + - 1) {
        ptr[row + a_idx] |= 1;
      }
      if (max == ((int )M[left]) + - 1) {
        ptr[row + a_idx] |= 2;
      }
    }
  }
// Trace-back
  index = 51 * 52;
  a_idx = 51;
  b_idx = 51;
  a_str_idx = 0;
  b_str_idx = 0;
  last_row_idx = (52 + 1) * 52 - 1;
  last_a_idx = (52 + 1) - 1;
  last_b_idx = (52 + 1) - 1;
  trace_row:
  while (a_idx > 0) {
    trace_col:
    while (b_idx > 0) {
      if (ptr[index] == 0) {
        a_idx--;
        b_idx--;
        a_str_idx++;
        b_str_idx++;
        alignedA[a_str_idx] = SEQA[a_idx];
        alignedB[b_str_idx] = SEQB[b_idx];
        index = b_idx * 52 + a_idx;
      }
       else {
        if (ptr[index] & 4) {
          a_idx--;
          b_idx--;
          a_str_idx++;
          b_str_idx++;
          alignedA[a_str_idx] = SEQA[a_idx];
          alignedB[b_str_idx] = SEQB[b_idx];
          index = b_idx * 52 + a_idx;
        }
         else {
          if (ptr[index] & 2) {
            b_idx--;
            b_str_idx++;
            alignedA[a_str_idx] = '-';
            alignedB[b_str_idx] = SEQB[b_idx];
            index = b_idx * 52 + a_idx;
          }
           else {
            if (ptr[index] & 1) {
              a_idx--;
              a_str_idx++;
              alignedA[a_str_idx] = SEQA[a_idx];
              alignedB[b_str_idx] = '-';
              index = b_idx * 52 + a_idx;
            }
          }
        }
      }
    }
    if (b_idx == 0) {
      b_idx = last_b_idx;
      a_idx = last_a_idx;
      b_str_idx = last_b_idx * 52;
      a_str_idx = last_a_idx * 52;
    }
     else {
      b_idx = 51;
    }
  }
  alignedA[a_str_idx] = (char )0;
  alignedB[b_str_idx] = (char )0;
}