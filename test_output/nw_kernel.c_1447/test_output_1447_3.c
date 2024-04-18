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
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    alignedA[a_idx] = ((char )0);
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    alignedB[b_idx] = ((char )0);
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  fill_out:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    fill_in:
    for (a_idx = 0; a_idx < 64; a_idx++) {
      if (a_idx == 0) {
        if (b_idx == 0) {
          score = 0;
        }
        else {
          score = 0 - 1 * 1;
        }
      }
      else {
        if (b_idx == 0) {
          score = 0 - 1 * 1;
        }
        else {
          row_up = 64 * (b_idx - 1);
          score = M[row_up + a_idx] + (((int )SEQA[a_idx]) == - 1 ? - 1 : ((int )SEQA[a_idx]) == 1 ? 1 : 0) - 1 * (((int )SEQB[b_idx]) == - 1 ? - 1 : ((int )SEQB[b_idx]) == 1 ? 1 : 0);
        }
      }
      M[64 * b_idx + a_idx] = score;
      if (a_idx == 0 || b_idx == 0) {
        ptr[64 * b_idx + a_idx] = 0;
      }
      else {
        up_left = M[64 * (b_idx - 1) + (a_idx - 1)];
        up = M[64 * (b_idx - 1) + a_idx];
        left = M[64 * b_idx + a_idx - 1];
        max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
        ptr[64 * b_idx + a_idx] = max == left ? 2 : max == up ? 1 : 0;
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  index = 16640;
  a_idx = 64;
  b_idx = 64;
  a_str_idx = 0;
  b_str_idx = 0;
  last_row_idx = 64 - 1;
  last_a_idx = 64 - 1;
  last_b_idx = 64 - 1;
  score = M[last_row_idx * 64 + last_a_idx];
  while(a_idx > 0 || b_idx > 0){
    if (ptr[last_row_idx * 64 + last_a_idx] == 0) {
      a_idx--;
      b_idx--;
      a_str_idx++;
      b_str_idx++;
    }
    else if (ptr[last_row_idx * 64 + last_a_idx] == 1) {
      a_idx--;
      b_str_idx++;
    }
    else {
      b_idx--;
      a_str_idx++;
      b_str_idx++;
    }
    last_row_idx = 64 * b_idx + a_idx;
    last_a_idx = a_idx;
    last_b_idx = b_idx;
    score = M[last_row_idx];
  }
  alignedA[a_str_idx] = 0;
  alignedB[b_str_idx] = 0;
}