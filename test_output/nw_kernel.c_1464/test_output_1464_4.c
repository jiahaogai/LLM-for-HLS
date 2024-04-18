#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[129],char alignedB[129],int M[1664],char ptr[1664])
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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  init_row:
  for (a_idx = 0; a_idx < 128L + 1L; a_idx++) {
    M[a_idx] = a_idx * - 1L;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 128L + 1L; b_idx++) {
    M[b_idx * (128L + 1L)] = b_idx * - 1L;
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_rowb:
  for (a_idx = 0; a_idx < 128L + 1L; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    init_colb:
    for (b_idx = 0; b_idx < 128L + 1L; b_idx++) {
      if (a_idx == 0) {
        M[b_idx] = b_idx * - 1L;
      } else {
        if (b_idx == 0) {
          M[a_idx * (128L + 1L)] = a_idx * - 1L;
        } else {
          a_str_idx = (a_idx * (128L + 1L)) + 1L;
          b_str_idx = (b_idx * (128L + 1L)) + 1L;
          up_left = ((int )M[a_str_idx - 1L]) + ((int )SEQA[a_idx - 1L]) * - 1L * ((int )SEQB[b_idx - 1L]);
          up = ((int )M[a_str_idx - 1L]) + ((int )'-') * - 1L * ((int )SEQB[b_idx]);
          left = ((int )M[b_str_idx - 1L]) + ((int )SEQA[a_idx]) * - 1L * ((int )'-');
          M[b_str_idx] = up_left;
          if (up > left) {
            max = up;
            row = a_idx - 1L;
            r = b_idx;
          } else {
            max = left;
            row = a_idx;
            r = b_idx - 1L;
          }
        }
      }
    }
  }
// TraceBack
  a_idx = 128L + 1L;
  b_idx = 128L + 1L;
  a_str_idx = (a_idx * (128L + 1L)) + 1L;
  b_str_idx = (b_idx * (128L + 1L)) + 1L;
  score = ((int )M[a_str_idx]) + ((int )SEQA[a_idx - 1L]) * - 1L * ((int )SEQB[b_idx - 1L]);
  ptr[0] = - 1L;
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  trace:
  while (1) {
    if (a_idx > 0L) {
      row_up = (a_idx - 1L) * (128L + 1L);
    }
    if (b_idx > 0L) {
      b_str_idx = (b_idx * (128L + 1L)) + 1L;
    }
    if (a_idx == 0L || b_idx == 0L) {
      score = 0L;
    }
    if (a_idx == 0L) {
      alignedA[a_idx] = '-';
      alignedB[b_idx] = SEQB[b_idx - 1L];
    } else {
      if (b_idx == 0L) {
        alignedA[a_idx] = SEQA[a_idx - 1L];
        alignedB[b_idx] = '-';
      } else {
        if (row_up == b_str_idx) {
          alignedA[a_idx] = SEQA[a_idx - 1L];
          alignedB[b_idx] = SEQB[b_idx - 1L];
          score = ((int )M[b_str_idx]) + ((int )SEQA[a_idx - 1L]) * - 1L * ((int )SEQB[b_idx - 1L]);
          ptr[((a_idx - 1L) * (128L + 1L)) + b_idx] = 2L;
        } else {
          if (a_str_idx == b_str_idx) {
            alignedA[a_idx] = SEQA[a_idx - 1L];
            alignedB[b_idx] = SEQB[b_idx - 1L];
            score = ((int )M[a_str_idx]) + ((int )SEQA[a_idx - 1L]) * - 1L * ((int )SEQB[b_idx - 1L]);
            ptr[((a_idx - 1L) * (128L + 1L)) + b_idx] = 1L;
          } else {
            if (((int )M[a_str_idx]) > ((int )(row + left))) {
              alignedA[a_idx] = SEQA[a_idx - 1L];
              alignedB[b_idx] = SEQB[b_idx - 1L];
              score = ((int )M[a_str_idx]) + ((int )SEQA[a_idx - 1L]) * - 1L * ((int )SEQB[b_idx - 1L]);
              ptr[((a_idx - 1L) * (128L + 1L)) + b_idx] = 1L;
            } else {
              if (((int )(row + left)) > ((int )M[b_str_idx])) {
                alignedA[a_idx] = SEQA[a_idx - 1L];
                alignedB[b_idx] = SEQB[b_idx - 1L];
                score = ((int )M[a_str_idx]) + ((int )SEQA[a_idx - 1L]) * - 1L * ((int )SEQB[b_idx - 1L]);
                ptr[((a_idx - 1L) * (128L + 1L)) + b_idx] = 2L;
              } else {
                if (((int )M[a_str_idx]) == ((int )(row + left))) {
                  if (ptr[((a_idx - 1L) * (128L + 1L)) + b_idx] == 2L) {
                    alignedA[a_idx] = alignedA[a_idx - 1L