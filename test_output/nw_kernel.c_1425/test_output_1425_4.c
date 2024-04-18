#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[128],char alignedB[128],char ptr[128],int M[128])
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
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
    ptr[a_idx] = 0;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
    ptr[b_idx + 5] = 0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  trace_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    a_str_idx = a_idx * 16;
    alignedB[a_idx * 2] = '_';
    alignedB[a_idx * 2 + 1] = '_';
    ptr[a_idx * 2] = 0;
    ptr[a_idx * 2 + 1] = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    trace_col:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      if (a_idx == 0 && b_idx == 0) {
        score = ((int )SEQA[0]) * ((int )SEQB[0]);
        M[0] = score;
      }
      else {
        if (a_idx == 0) {
          up_left = M[b_idx * 2] + ((int )SEQA[0]) * ((int )SEQB[b_idx]);
          up = M[(b_idx + 1) * 2] + ((int )SEQA[0]);
          left = M[(b_idx * 2) + 1] + ((int )SEQB[0]);
          max = (up_left > ((up > left?up:left))?up_left:((up > left?up:left)));
          M[b_idx * 2] = left;
          ptr[b_idx * 2] = 2;
        }
        else {
          if (b_idx == 0) {
            up_left = M[a_idx * 2] + ((int )SEQA[a_idx]) * ((int )SEQB[0]);
            up = M[(a_idx + 1) * 2] + ((int )SEQA[a_idx]);
            left = M[(a_idx * 2) + 1] + ((int )SEQB[0]);
            max = (up_left > ((up > left?up:left))?up_left:((up > left?up:left)));
            M[a_idx * 2] = up;
            ptr[a_idx * 2] = 1;
          }
          else {
            up_left = M[(a_idx * 2) + 1 + b_idx * 2] + ((int )SEQA[a_idx]) * ((int )SEQB[b_idx]);
            up = M[(a_idx + 1) * 2 + b_idx * 2] + ((int )SEQA[a_idx]) + ((int )SEQB[b_idx]);
            left = M[(a_idx * 2) + 1 + (b_idx + 1) * 2] + ((int )SEQB[b_idx]);
            max = (up_left > ((up > left?up:left))?up_left:((up > left?up:left)));
            M[a_idx * 2 + 1 + b_idx * 2] = max;
            if (up_left == max) {
              ptr[a_idx * 2 + 1 + b_idx * 2] = 3;
            }
            
#pragma ACCEL PIPELINE auto{__PIPE__L2}
            
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
            
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
            if (up == max) {
              ptr[a_idx * 2 + 1 + b_idx * 2] = 1;
            }
            
#pragma ACCEL PIPELINE auto{__PIPE__L3}
            
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
            
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
            if (left == max) {
              ptr[a_idx * 2 + 1 + b_idx * 2] = 2;
            }
          }
        }
        alignedA[a_idx * 2] = ((char )((int )SEQA[a_idx]));
        alignedA[a_idx * 2 + 1] = 45;
        alignedB[a_idx * 2] = ((char )((int )SEQB[b_idx]));
        alignedB[a_idx * 2 + 1] = 45;
      }
    }
    alignedB[a_idx * 2 + 1] = '_';
  }
  row = 5 * 2 - 1;
  b_idx = 5 - 1;
  a_idx = 5 - 1;
  a_str_idx = a_idx * 16;
  b_str_idx = b_idx * 16;
/* Follow the trace back starting from the bottom right corner */
  
#pragma ACCEL PIPELINE auto{__PIPE__L4}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
  trace_back:
  while (a_idx != 0 || b_idx != 0) {
    if (ptr[a_idx * 2 + b_idx * 2] == 1) {
      up = a_idx * 2;
      a_idx = up;
      b_str_idx = b_idx * 16;
    }
    else {
      if (ptr[a_idx * 2 + b_idx * 2] == 2) {
        left = a_idx * 2 + 1;
        a_idx = left;
        a_str_idx = a_idx * 16;
      }
      else {
        up_left = a_idx * 2 + b_idx * 2;
        a_idx = up_left;
        b_str_idx = b_idx * 16;
      }
    }
    if (ptr[a_idx * 2 + b_idx * 2] == 2) {
      left = b_idx * 2 + 1;
      b_idx = left;
      a_str_idx = a_idx * 16;
    }
    else {
      if (ptr[a_idx * 2 + b_idx * 2] == 3) {
        up = b_idx * 2;
        b_idx = up;
        b_str_idx = b_idx * 16;
      }
      else {
        up_left = a_idx * 2 + b_idx * 2;
        b_idx = up_left;
        b_