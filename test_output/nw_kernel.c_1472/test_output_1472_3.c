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
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
  }
  alignedA[a_idx] = 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  alignedB[b_idx] = 0;
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  init_score:
  for (b_idx = 0; b_idx < 5; b_idx++) {
//#pragma ACCEL PARALLEL FACTOR=auto{1}
    init_score_a:
    for (a_idx = 0; a_idx < 5; a_idx++) {
      if (a_idx == 0 || b_idx == 0) {
        if (a_idx == 0 && b_idx == 0) {
          M[0] = 0;
        }
        else if (a_idx == 0) {
          M[b_idx * 6] = (((int )SEQB[b_idx]) * -1);
        }
        else {
          M[b_idx * 6] = (((int )SEQB[b_idx]) * -1) + M[(b_idx - 1) * 6];
        }
      }
      else {
        if ((int )SEQA[a_idx] == (int )SEQB[b_idx]) {
          score = 1;
        }
        else {
          score = -1;
        }
        row_up = (b_idx * 6);
        up_left = row_up + a_idx - 1;
        up = row_up + a_idx;
        left = up_left + 1;
        max = M[up_left] + score;
        if (max < ((int )SEQA[a_idx] * -1)) {
          max = ((int )SEQA[a_idx] * -1);
        }
        if (max < M[up] + -1) {
          max = M[up] + -1;
        }
        if (max < M[left] + -1) {
          max = M[left] + -1;
        }
        M[up_left] = max;
//#pragma ACCEL PIPELINE auto{__PIPE__L3}
//#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
        if (max == ((int )SEQA[a_idx] * -1)) {
          ptr[up_left] = 3;
        }
        else {
          if (max == M[up] + -1) {
            ptr[up_left] = 2;
          }
          else {
            if (max == M[left] + -1) {
              ptr[up_left] = 1;
            }
            else {
              ptr[up_left] = 0;
            }
          }
        }
        if (a_idx > 0) {
          if (b_idx > 0) {
            a_str_idx = ((a_idx - 1) * 6);
            b_str_idx = ((b_idx - 1) * 6);
            if (M[a_str_idx] >= M[b_str_idx] && M[a_str_idx] >= M[a_str_idx + 1] && M[a_str_idx] >= M[b_str_idx + 1]) {
              ptr[up_left] = 5;
            }
            else if (M[b_str_idx] >= M[a_str_idx] && M[b_str_idx] >= M[a_str_idx + 1] && M[b_str_idx] >= M[b_str_idx + 1]) {
              ptr[up_left] = 6;
            }
            else if (M[a_str_idx + 1] >= M[b_str_idx] && M[a_str_idx + 1] >= M[a_str_idx] && M[a_str_idx + 1] >= M[b_str_idx + 1]) {
              ptr[up_left] = 7;
            }
            else if (M[b_str_idx + 1] >= M[a_str_idx] && M[b_str_idx + 1] >= M[a_str_idx + 1] && M[b_str_idx + 1] >= M[a_str_idx]) {
              ptr[up_left] = 8;
            }
          }
        }
      }
    }
  }
/* TraceBack */
  a_idx = 4;
  b_idx = 4;
  r = 5;
  a_str_idx = (a_idx * 6);
  b_str_idx = (b_idx * 6);
  alignedA[a_idx + 1] = 0;
  alignedB[b_idx + 1] = 0;
  while(1) {
    if (ptr[b_str_idx] == 0) {
      alignedA[a_idx] = SEQA[a_idx];
      alignedB[b_idx] = SEQB[b_idx];
      a_idx --;
      b_idx --;
      a_str_idx = (a_idx * 6);
      b_str_idx = (b_idx * 6);
    }
    else if (ptr[b_str_idx] == 1) {
      alignedA[a_idx] = SEQA[a_idx];
      alignedB[b_idx] = '-';
      a_idx --;
      b_str_idx ++;
    }
    else if (ptr[b_str_idx] == 2) {
      alignedA[a_idx] = '-';
      alignedB[b_idx] = SEQB[b_idx];
      b_idx --;
      b_str_idx ++;
    }
    else if (ptr[b_str_idx] == 3) {
      alignedA[a_idx] = SEQA[a_idx];
      alignedB[b_idx] = SEQB[b_idx];
      a_idx --;
      b_idx --;
      a_str_idx = (a_idx * 6);
      b_str_idx = (b_idx * 6);
    }
    else if (ptr[b_str_idx] == 4) {
      alignedA[a_idx] = SEQA[a_idx];
      alignedB[b_idx] = '-';
      a_idx --;
      b_str_idx = a_str_idx;
    }
    else if (ptr[b_str_idx] == 5) {
      alignedA[a_idx] = '-';
      alignedB[b_idx] = SEQB[b_idx];
      b_idx --;
      b_str_idx = a_str_idx;
    }
    else if (ptr[b_str_idx] == 6) {
      alignedA[