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
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx + 128] = '-';
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx + 128] = '-';
  }
// Matrix multiplication
//   A[0]B[0]
//   A[0]B[1]
//   A[0]B[2]
//   A[0]B[3]
//   A[0]B[4]
//   A[1]B[0]
//   A[1]B[1]
//   A[1]B[2]
//   A[1]B[3]
//   A[1]B[4]
//   A[2]B[0]
//   A[2]B[1]
//   A[2]B[2]
//   A[2]B[3]
//   A[2]B[4]
//   A[3]B[0]
//   A[3]B[1]
//   A[3]B[2]
//   A[3]B[3]
//   A[3]B[4]
//   A[4]B[0]
//   A[4]B[1]
//   A[4]B[2]
//   A[4]B[3]
//   A[4]B[4]
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  loop_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    loop_col:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      if (((int )SEQA[a_idx]) == ((int )SEQB[b_idx])) {
        score = 1;
      }
       else {
        score = -1;
      }
      row_up = a_idx * 5;
      up_left = score + M[row_up + (b_idx + 0)];
      up = M[row_up + (b_idx + 0)] + -1;
      left = M[(a_idx + 0) * 5 + (b_idx + 0)] + -1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[a_idx * 5 + b_idx] = max;
      if (max == left) {
        ptr[a_idx * 5 + b_idx] = 2;
      }
       else {
        if (max == up) {
          ptr[a_idx * 5 + b_idx] = 1;
        }
         else {
          ptr[a_idx * 5 + b_idx] = 0;
        }
      }
    }
  }
// TraceBack
    a_idx = 4;
    b_idx = 4;
    a_str_idx = 0;
    b_str_idx = 0;
    r = M[a_idx * 5 + b_idx];
    while (a_idx != 0 || b_idx != 0) {
      row_up = a_idx * 5;
      if (ptr[row_up + b_idx] == 2) {
        a_idx = a_idx - 1;
        b_idx = b_idx - 1;
        alignedA[a_str_idx++] = SEQA[a_idx];
        alignedB[b_str_idx++] = SEQB[b_idx];
        r = M[a_idx * 5 + b_idx];
      }
       else {
        if (ptr[row_up + b_idx] == 1) {
          a_idx = a_idx - 1;
          alignedA[a_str_idx++] = SEQA[a_idx];
          alignedB[b_str_idx++] = '-';
          r = M[a_idx * 5 + b_idx];
        }
         else {
          b_idx = b_idx - 1;
          alignedA[a_str_idx++] = '-';
          alignedB[b_str_idx++] = SEQB[b_idx];
          r = M[a_idx * 5 + b_idx];
        }
      }
    }
}