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
  for (a_idx = 0; a_idx < 5; a_idx++) {
    M[a_idx] = a_idx * - 1;
    alignedA[a_idx] = '-';
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx * - 1;
    alignedB[b_idx] = '-';
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  fill_out:
  for (b_idx = 1; b_idx < 5; b_idx++) {
    b_str_idx = b_idx * 5;
    
#pragma ACCEL PARALLEL FACTOR=auto{128}
    fill_in:
    for (a_idx = 1; a_idx < 5; a_idx++) {
      a_str_idx = a_idx * 5;
      score = ((int )SEQA[a_str_idx - 1]) == ((int )SEQB[b_str_idx - 1]) ? 1 : ((int )SEQA[a_str_idx - 1]) == ((int )'-') ? - 1 : - 1;
      up_left = M[a_str_idx - 1 + b_str_idx - 1] + score;
      up = M[a_str_idx - 1 + b_str_idx] - 1;
      left = M[a_str_idx + b_str_idx - 1] - 1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[a_str_idx + b_str_idx] = max;
      if (max == left) {
        ptr[a_str_idx + b_str_idx] = 2;
      }
      
      if (max == up) {
        ptr[a_str_idx + b_str_idx] = 1;
      }
      
      if (max == up_left) {
        ptr[a_str_idx + b_str_idx] = 0;
      }
    }
  }
  row = 5;
  b_idx = 5;
  a_idx = 4;
  b_str_idx = 25;
  a_str_idx = 20;
  index = b_idx * a_idx;
  last_row_idx = (b_idx - 1) * a_idx;
  last_a_idx = a_idx - 1;
  last_b_idx = b_idx - 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  traceback:
  while (1) {
    if (b_idx == 0 && a_idx == 0) {
      break;
    }
    if (b_idx == 0) {
      alignedA[a_idx ++] = '-';
    }
    if (a_idx == 0) {
      alignedB[b_idx ++] = '-';
    }
    if (ptr[a_str_idx + b_str_idx] == 0) {
      alignedA[a_idx] = SEQA[a_str_idx];
      alignedB[b_idx] = SEQB[b_str_idx];
      a_str_idx -= 1;
      b_str_idx -= 1;
      a_idx ++;
      b_idx ++;
    }
    if (ptr[a_str_idx + b_str_idx] == 1) {
      alignedA[a_idx] = SEQA[a_str_idx];
      alignedB[b_idx] = '-';
      a_str_idx -= 1;
      a_idx ++;
    }
    if (ptr[a_str_idx + b_str_idx] == 2) {
      alignedA[a_idx] = '-';
      alignedB[b_idx] = SEQB[b_str_idx];
      b_str_idx -= 1;
      b_idx ++;
    }
  }
}