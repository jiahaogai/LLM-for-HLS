### Function Body:
c
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
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    M[a_idx] = a_idx;
    ptr[a_idx] = -1;
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 64] = b_idx;
    ptr[b_idx * 64] = -1;
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  fill_out:
  for (b_idx = 1; b_idx < 5; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    fill_in:
    for (a_idx = 1; a_idx < 5; a_idx++) {
      if (((int )SEQA[a_idx + -1]) == ((int )SEQB[b_idx + -1])) {
        score = 1;
      }
       else {
        score = -1;
      }
      up_left = M[(b_idx + -1) * 64] + a_idx;
      up = M[b_idx * 64] + a_idx + -1;
      left = M[b_idx * 64 + a_idx + -1] + score;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[b_idx * 64 + a_idx] = max;
      if (max == left) {
        ptr[b_idx * 64 + a_idx] = a_idx + -1;
      }
       else {
        if (max == up) {
          ptr[b_idx * 64 + a_idx] = b_idx + -1;
        }
         else {
          ptr[b_idx * 64 + a_idx] = up_left;
        }
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  row = 5;
  b_idx = 5;
  a_idx = 5;
  a_str_idx = 0;
  b_str_idx = 0;
/*
    trace: while(a_idx>0 || b_idx>0) {
        row = b_idx * 64;
        if (a_idx < 0) {
            a_idx = -a_idx;
            b_idx = ptr[row + a_idx];
            alignedB[b_str_idx++] = '_';
        }
        else if (b_idx < 0) {
            b_idx = -b_idx;
            a_idx = ptr[row + a_idx];
            alignedA[a_str_idx++] = '_';
        }
        else if (M[row + a_idx] == M[row + a_idx + 1] + 1 && SEQA[a_idx] == SEQB[b_idx]) {
            a_idx++;
            b_idx++;
            alignedA[a_str_idx++] = SEQA[a_idx];
            alignedB[b_str_idx++] = SEQB[b_idx];
        }
        else if (M[row + a_idx] == M[row + a_idx + 1] + 1 && SEQA[a_idx] != SEQB[b_idx]) {
            a_idx++;
            alignedA[a_str_idx++] = SEQA[a_idx];
            alignedB[b_str_idx++] = '_';
        }
        else if (M[row + a_idx] == M[row + a_idx + 1] - 1 && SEQA[a_idx] == SEQB[b_idx]) {
            a_idx++;
            alignedA[a_str_idx++] = SEQA[a_idx];
            alignedB[b_str_idx++] = SEQB[b_idx];
            b_idx++;
        }
        else if (M[row + a_idx] == M[row + a_idx + 1] - 1 && SEQA[a_idx] != SEQB[b_idx]) {
            a_idx++;
            alignedA[a_str_idx++] = '_';
            alignedB[b_str_idx++] = SEQB[b_idx];
        }
        else if (M[row + a_idx] == M[row + a_idx - 1] + 1 && SEQA[a_idx] == SEQB[b_idx]) {
            b_idx++;
            alignedA[a_str_idx++] = SEQA[a_idx];
            alignedB[b_str_idx++] = SEQB[b_idx];
            a_idx++;
        }
        else if (M[row + a_idx] == M[row + a_idx - 1] + 1 && SEQA[a_idx] != SEQB[b_idx]) {
            b_idx++;
            alignedA[a_str_idx++] = '_';
            alignedB[b_str_idx++] = SEQB[b_idx];
        }
        else if (M[row + a_idx] == M[row + a_idx - 1] - 1 && SEQA[a_idx] == SEQB[b_idx]) {
            b_idx++;
            alignedA[a_str_idx++] = SEQA[a_idx];
            alignedB[b_str_idx++] = SEQB[b_idx];
        }
        else if (M[row + a_idx] == M[row + a_idx - 1] - 1 && SEQA[a_idx] != SEQB[b_idx]) {
            b_idx++;
            alignedA[a_str_idx++] = SEQA[a_idx];
            alignedB[b_str_idx++] = '_';
        }
    }
    alignedA[a_str_idx] = 0;
    alignedB[b_str_idx] = 0;
*/
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  trace:
  while(a_idx > 0 || b_idx > 0){
    row = b_idx * 64;
    if (a_idx < 0) {
      a_idx = -a_idx;
      b_idx = ptr[row + a_idx];
      alignedB[b_str_idx++] = '_';
    }
     else if (b_idx < 0) {
      b_idx = -b_idx;
      a_idx = ptr[row + a_idx];
      alignedA[a_str_idx++] = '_';
    }
     else if (M[row + a_idx] == (M[row + a_idx + 1] + 1) && ((int )SEQA[a_idx]) == ((int )SEQB[b_idx])) {
      a_idx++;
      b_idx++;
      alignedA[a_str_idx++] = SEQA[a_idx];