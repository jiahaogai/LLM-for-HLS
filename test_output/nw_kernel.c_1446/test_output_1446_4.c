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
  int a_str_idx_p1;
  int b_str_idx_p1;
  char a_char;
  char b_char;
  int idx;
  int idx_col;
  int idx_row;
  int idx_row_up;
//#pragma scop
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    M[a_idx] = a_idx;
    ptr[a_idx] = - 1;
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx;
    ptr[b_idx * 5] = - 1;
  }
// Loop for loading A
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  read_A:
  for (a_idx = 0; a_idx < 5; a_idx++) {
// Loop for loading B
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    read_B:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      a_char = SEQA[a_idx];
      b_char = SEQB[b_idx];
      a_str_idx = a_idx * 5;
      b_str_idx = b_idx * 5;
      a_str_idx_p1 = a_str_idx + 1;
      b_str_idx_p1 = b_str_idx + 1;
      score = ((int )a_char) * ((int )b_char);
      up_left = M[b_str_idx] + ((int )a_char) * ((int )b_char);
      up = M[b_str_idx_p1] + ((int )a_char);
      left = M[a_str_idx_p1] + ((int )b_char);
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[b_str_idx_p1] = max;
      if (max == left) {
        ptr[b_str_idx_p1] = a_str_idx_p1;
      }
      else {
        if (max == up) {
          ptr[b_str_idx_p1] = b_str_idx_p1;
        }
        else {
          ptr[b_str_idx_p1] = a_str_idx_p1;
        }
      }
    }
  }
// TraceBack
  row = 4;
  b_idx = 4;
  a_idx = ptr[b_idx * 5 + 4];
  alignedA[0] = SEQA[a_idx];
  alignedB[0] = SEQB[b_idx];
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  trace:
  while (a_idx != 0 || b_idx != 0) {
    if (a_idx == - 1) {
      a_idx = a_idx;
    }
    else {
      if (b_idx == - 1) {
        b_idx = b_idx;
      }
      else {
        if (a_idx > b_idx) {
          a_idx = ptr[b_idx * 5 + a_idx];
          alignedA[row] = SEQA[a_idx];
          alignedB[row] = SEQB[b_idx];
          row_up = b_idx * 5;
          b_idx = ptr[row_up + 4];
        }
        else {
          if (a_idx < b_idx) {
            b_idx = ptr[a_idx * 5 + b_idx];
            alignedA[row] = SEQA[a_idx];
            alignedB[row] = SEQB[b_idx];
            row_up = a_idx * 5;
            a_idx = ptr[row_up + 4];
          }
          else {
            a_idx = ptr[b_idx * 5 + a_idx];
            alignedA[row] = SEQA[a_idx];
            alignedB[row] = SEQB[b_idx];
            row_up = b_idx * 5;
            b_idx = ptr[row_up + 4];
          }
        }
      }
    }
    row++;
  }
//#pragma endscop
}