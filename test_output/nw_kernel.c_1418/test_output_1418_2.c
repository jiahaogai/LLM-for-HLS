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
  int next_idx;
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_row:
  for (a_idx = 0; a_idx < 16; a_idx++) {
    M[a_idx] = a_idx * - 1;
    ptr[a_idx] = ((char )0);
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  init_col:
  for (b_idx = 0; b_idx < 16; b_idx++) {
    M[b_idx * 16] = b_idx * - 1;
    ptr[b_idx * 16] = ((char )'\000');
  }
// Matrix multiplication
//  
// 

#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  loop_row:
  for (a_idx = 0; a_idx < 15; a_idx++) {
    a_str_idx = a_idx * 16;
    a_str_idx_p1 = (a_idx + 1) * 16;
    row_up = (a_idx == 0) ? - 1 : a_idx * 16;
    row = a_idx * 16;
// Matrix multiplication
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    loop_col:
    for (b_idx = 0; b_idx < 15; b_idx++) {
      b_str_idx = b_idx * 16;
      b_str_idx_p1 = (b_idx + 1) * 16;
      left = b_idx * 16;
      up_left = M[row_up + b_idx * 16];
      up = M[row_up + b_str_idx];
      max = (up_left > up) ? (up_left > ((b_idx == 0) ? - 1 : M[row + b_str_idx_p1])) ? up_left : ((b_idx == 0) ? - 1 : M[row + b_str_idx_p1]) : (up > ((b_idx == 0) ? - 1 : M[row + b_str_idx_p1])) ? up : ((b_idx == 0) ? - 1 : M[row + b_str_idx_p1]);
      score = ((int )SEQA[a_str_idx_p1]) == - 1 ? - 1 : ((int )SEQA[a_str_idx_p1]) == ((int )SEQB[b_str_idx_p1]) ? 1 : - 1;
      M[row + b_str_idx] = score + max;
      if (max == left) {
        ptr[row + b_str_idx] = ((char )'L');
      }
      else {
        if (max == up) {
          ptr[row + b_str_idx] = ((char )'U');
        }
        else {
          ptr[row + b_str_idx] = ptr[row_up + b_str_idx_p1];
        }
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
    idx = 0;
    r = 15 * 16 - 1;
    a_idx = 15;
    b_idx = 15;
    a_str_idx = a_idx * 16;
    b_str_idx = b_idx * 16;
    a_str_idx_p1 = (a_idx + 1) * 16;
    b_str_idx_p1 = (b_idx + 1) * 16;
    next_idx = M[r] + ((int )SEQA[a_str_idx_p1]) == - 1 ? - 1 : ((int )SEQA[a_str_idx_p1]) == ((int )SEQB[b_str_idx_p1]) ? 1 : - 1;
    while(1) {
      if (ptr[r] == ((char )'L')) {
        b_idx = (b_idx + 1) - 1;
        b_str_idx = b_idx * 16;
        b_str_idx_p1 = (b_idx + 1) * 16;
        next_idx = M[r] + ((int )SEQA[a_str_idx_p1]) == - 1 ? - 1 : ((int )SEQA[a_str_idx_p1]) == ((int )SEQB[b_str_idx_p1]) ? 1 : - 1;
      }
      else {
        if (ptr[r] == ((char )'U')) {
          a_idx = (a_idx + 1) - 1;
          a_str_idx = a_idx * 16;
          a_str_idx_p1 = (a_idx + 1) * 16;
          next_idx = M[r] + ((int )SEQA[a_str_idx_p1]) == - 1 ? - 1 : ((int )SEQA[a_str_idx_p1]) == ((int )SEQB[b_str_idx_p1]) ? 1 : - 1;
        }
        else {
          a_idx = (a_idx + 1) - 1;
          b_idx = (b_idx + 1) - 1;
          a_str_idx = a_idx * 16;
          b_str_idx = b_idx * 16;
          a_str_idx_p1 = (a_idx + 1) * 16;
          b_str_idx_p1 = (b_idx + 1) * 16;
          next_idx = M[r] + ((int )SEQA[a_str_idx_p1]) == - 1 ? - 1 : ((int )SEQA[a_str_idx_p1]) == ((int )SEQB[b_str_idx_p1]) ? 1 : - 1;
        }
      }
      r = next_idx + b_idx * 16;
      if (a_idx == 0 && b_idx == 0) {
        break;
      }
    }
    alignedA[idx] = ((char )'\000');
    alignedB[idx] = ((char )'\000');
    padA:
    for (a_idx = 0; a_idx < 16; a_idx++) {
      a_str_idx = a_idx * 16;
      padB:
      for (b_idx = 0; b_idx < 16; b_idx++) {
        b_str_idx = b_idx * 16;
        if (((int )SEQA[a_str_idx]) != - 1