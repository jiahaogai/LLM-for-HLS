#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[128],char alignedB[128],char M[128][128],char ptr[128][128])
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
  for (a_idx = 0; a_idx < 128; a_idx++) {
    alignedA[a_idx] = ((char )0);
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 128; b_idx++) {
    alignedB[b_idx] = ((char )0);
  }
// Matrix initialization
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  init_mat:
  for (a_idx = 0; a_idx < 128; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    init_row_v2:
    for (b_idx = 0; b_idx < 128; b_idx++) {
      if (a_idx == 0 && b_idx == 0) {
        M[a_idx][b_idx] = 0;
      }
      else if (a_idx == 0) {
        M[a_idx][b_idx] = M[a_idx][b_idx + 1] + 1;
        ptr[a_idx][b_idx] = 5;
      }
      else if (b_idx == 0) {
        M[a_idx][b_idx] = M[a_idx + 1][b_idx] + 1;
        ptr[a_idx][b_idx] = 3;
      }
      else {
        up_left = M[a_idx - 1][b_idx - 1] + ((int )SEQA[a_idx] == (int )SEQB[b_idx] ? 0 : 1);
        up = M[a_idx - 1][b_idx] + 1;
        left = M[a_idx][b_idx - 1] + 1;
        M[a_idx][b_idx] = (up_left < up ? (up_left < left ? up_left : left) : (up < left ? up : left));
        if (up_left < up) {
          if (up_left < left) {
            ptr[a_idx][b_idx] = 4;
          }
          else {
            ptr[a_idx][b_idx] = 2;
          }
        }
        else {
          if (up < left) {
            ptr[a_idx][b_idx] = 1;
          }
          else {
            ptr[a_idx][b_idx] = 0;
          }
        }
      }
    }
  }
// TraceBack
  row = 127;
  b_idx = 127;
  a_str_idx = 0;
  b_str_idx = 0;
/*
    row = 127
    b_idx = 127
    a_str_idx = 0
    b_str_idx = 0
    score = M[row][b_idx]
    while (row > 0 || b_idx > 0) {
      if (ptr[row][b_idx] == 5) {
        a_idx = row;
        b_idx = b_idx;
      }
      else if (ptr[row][b_idx] == 4) {
        a_idx = row - 1;
        b_idx = b_idx - 1;
        alignedA[a_str_idx] = SEQA[a_idx];
        alignedB[b_str_idx] = SEQB[b_idx];
        a_str_idx++;
        b_str_idx++;
      }
      else if (ptr[row][b_idx] == 3) {
        a_idx = row;
        b_idx = b_idx - 1;
      }
      else if (ptr[row][b_idx] == 2) {
        a_idx = row - 1;
        b_idx = b_idx - 1;
        alignedA[a_str_idx] = SEQA[a_idx];
        alignedB[b_str_idx] = SEQB[b_idx];
        a_str_idx++;
        b_str_idx++;
      }
      else if (ptr[row][b_idx] == 1) {
        a_idx = row - 1;
        b_idx = b_idx;
      }
      else {
        a_idx = row;
        b_idx = b_idx;
      }
      row_up = row;
      row = a_idx;
      b_idx_up = b_idx;
      b_idx = b_idx_tmp;
    }
    alignedA[a_str_idx] = 0;
    alignedB[b_str_idx] = 0;
*/
}