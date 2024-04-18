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
  int index;
  int last_row_idx;
  int last_a_idx;
  int last_b_idx;
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_row:
  for (a_idx = 0; a_idx < 128 + 1; a_idx++) {
    M[a_idx] = a_idx * - 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  init_col:
  for (b_idx = 0; b_idx < 128 + 1; b_idx++) {
    M[b_idx * (128 + 1)] = b_idx * - 1;
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  fill_out:
  for (b_idx = 1; b_idx < 128 + 1; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    fill_a:
    for (a_idx = 1; a_idx < 128 + 1; a_idx++) {
      if (((int )SEQA[a_idx - 1]) == ((int )SEQB[b_idx - 1])) {
        score = 1;
      }
       else {
        score = - 1;
      }
      row_up = (b_idx - 1) * (128 + 1);
      up_left = M[row_up + (a_idx - 1)] + score;
      up = M[row_up + a_idx] + - 1;
      left = M[b_idx + (a_idx - 1)] + - 1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[b_idx * (128 + 1) + a_idx] = max;
      if (max == left) {
        ptr[b_idx * (128 + 1) + a_idx] = 2;
      }
       else {
        if (max == up) {
          ptr[b_idx * (128 + 1) + a_idx] = 1;
        }
         else {
          ptr[b_idx * (128 + 1) + a_idx] = 0;
        }
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  index = ((128 + 1) * (128 + 1)) - 1;
  a_idx = 128;
  b_idx = 128;
  last_row_idx = ((128 + 1) * (128 + 1)) - 1 + (- 1) * (128 + 1);
  last_a_idx = 128 + (- 1);
  last_b_idx = 128 + (- 1);
  trace: while(a_idx > 0 || b_idx > 0) {
    row = b_idx * (128 + 1);
    if (ptr[row + a_idx] == 0) {
      a_str_idx = a_idx - 1;
      b_str_idx = b_idx - 1;
    }
     else {
      if (ptr[row + a_idx] == 1) {
        a_str_idx = a_idx - 1;
        b_str_idx = b_idx;
        b_idx = b_idx - 1;
      }
       else {
        a_str_idx = a_idx;
        b_str_idx = b_idx - 1;
        a_idx = a_idx - 1;
      }
    }
    alignedA[index] = ((char )((int )SEQA[a_str_idx]));
    alignedB[index] = ((char )((int )SEQB[b_str_idx]));
    index--;
  }
}