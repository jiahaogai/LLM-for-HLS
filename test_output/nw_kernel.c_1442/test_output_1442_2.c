#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[129],char alignedB[129],char ptr[129],int M[16641])
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
  for (a_idx = 0; a_idx < 128L + 1; a_idx++) {
    M[a_idx] = a_idx * - 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 128L + 1; b_idx++) {
    M[b_idx * (128L + 1)] = b_idx * - 1;
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (b_idx = 1; b_idx < 128L + 1; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (a_idx = 1; a_idx < 128L + 1; a_idx++) {
      score = ((int )SEQA[a_idx - 1]) * ((int )SEQB[b_idx - 1]) * 1;
      row_up = (b_idx - 1) * (128L + 1);
      row = b_idx * (128L + 1);
      up_left = row_up + (a_idx - 1);
      up = row_up + a_idx;
      left = row + (a_idx - 1);
      max = (M[up_left] + score);
      if (max > ((M[up] + ((int )'D')))) {
        max = (M[up] + ((int )'D'));
      }
      if (max > ((M[left] + ((int )'I')))) {
        max = (M[left] + ((int )'I'));
      }
      M[row + a_idx] = max;
      if (max == ((M[up_left] + ((int )'D')))) {
        ptr[row + a_idx] = 2;
      }
      else {
        if (max == ((M[up] + ((int )'D')))) {
          ptr[row + a_idx] = 3;
        }
        else {
          if (max == ((M[left] + ((int )'I')))) {
            ptr[row + a_idx] = 4;
          }
        }
      }
    }
  }
// TraceBack
  a_idx = 128L + 1;
  b_idx = 128L + 1;
  a_str_idx = 0;
  b_str_idx = 0;
/*
    traceBack: while(a_idx>0 && b_idx>0) {
      r = b_idx*(ALEN + 1);
      if (ptr[r + a_idx] == 2) {
        a_idx--;
        b_idx--;
        alignedA[a_str_idx++] = SEQA[a_idx];
        alignedB[b_str_idx++] = SEQB[b_idx];
      }
      else if (ptr[r + a_idx] == 3) {
        a_idx--;
        alignedA[a_str_idx++] = SEQA[a_idx];
        alignedB[b_str_idx++] = '-';
      }
      else if (ptr[r + a_idx] == 4) {
        b_idx--;
        alignedA[a_str_idx++] = '-';
        alignedB[b_str_idx++] = SEQB[b_idx];
      }
    }
    if (a_idx == 0) {
      while(b_idx > 0) {
        b_idx--;
        alignedA[a_str_idx++] = '-';
        alignedB[b_str_idx++] = SEQB[b_idx];
      }
    }
    else if (b_idx == 0) {
      while(a_idx > 0) {
        a_idx--;
        alignedA[a_str_idx++] = SEQA[a_idx];
        alignedB[b_str_idx++] = '-';
      }
    }
*/
}