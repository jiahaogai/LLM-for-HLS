#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[128],char alignedB[128],int M[1664],char ptr[1664])
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
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    M[a_idx] = a_idx * - 1;
    ptr[a_idx] = - 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx * - 1;
    ptr[b_idx * 5] = - 1;
  }
// Matrix multiplication loop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  fill_out:
  for (b_idx = 1; b_idx < 5; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    fill_in:
    for (a_idx = 1; a_idx < 5; a_idx++) {
      score = ((int )SEQA[a_idx - 1]) - 97 < ((int )SEQB[b_idx - 1]) - 97 ? ((int )SEQA[a_idx - 1]) - 97 : ((int )SEQB[b_idx - 1]) - 97;
      up_left = M[(b_idx - 1) * 5] + score;
      score = ((int )SEQA[a_idx - 1]) - 97 > ((int )SEQB[b_idx - 1]) - 97 ? ((int )SEQA[a_idx - 1]) - 97 : ((int )SEQB[b_idx - 1]) - 97;
      up = M[b_idx * 5] + score;
      left = M[(a_idx - 1) + b_idx * 5] + - 1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[a_idx + b_idx * 5] = max;
      if (max == up_left) {
        ptr[a_idx + b_idx * 5] = a_idx - 1 + (b_idx - 1) * 5;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
      if (max == up) {
        ptr[a_idx + b_idx * 5] = a_idx - 1 + b_idx * 5;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      if (max == left) {
        ptr[a_idx + b_idx * 5] = a_idx - 1 + (b_idx - 1) * 5;
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  row = 4;
  b_idx = 4;
  a_idx = 4;
  a_str_idx = 0;
  b_str_idx = 0;
/*
    trace_out:
    while (a_idx != 0 || b_idx != 0) {
      row_up = a_idx - 1 + b_idx * 5;
      if (b_idx == 0) {
        a_idx--;
        a_str_idx++;
        alignedA[a_str_idx] = SEQA[a_idx];
        alignedB[b_str_idx] = '_';
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L4}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      else if (a_idx == 0) {
        b_idx--;
        b_str_idx++;
        alignedA[a_str_idx] = '_';
        alignedB[b_str_idx] = SEQB[b_idx];
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L5}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      else if (M[a_idx + b_idx * 5] > M[row_up] && M[a_idx + b_idx * 5] > M[a_idx + (b_idx - 1) * 5]) {
        b_idx--;
        b_str_idx++;
        alignedA[a_str_idx] = '_';
        alignedB[b_str_idx] = SEQB[b_idx];
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L6}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
      else if (M[row_up] > M[a_idx + (b_idx - 1) * 5]) {
        a_idx--;
        a_str_idx++;
        alignedA[a_str_idx] = SEQA[a_idx];
        alignedB[b_str_idx] = SEQB[b_idx];
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L7}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
      else {
        a_idx--;
        b_idx--;
        a_str_idx++;
        b_str_idx++;
        alignedA[a_str_idx] = SEQA[a_idx];
        alignedB[b_str_idx] = SEQB[b_idx];
      }
    }
  }
*/
}