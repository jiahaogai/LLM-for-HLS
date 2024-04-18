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
  alignedA[a_idx] = ((void *)0);
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  alignedB[b_idx] = ((void *)0);
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_score:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedB[a_idx + 5] = '_';
    a_str_idx = a_idx * 16;
    b_str_idx = a_idx * 4;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    fill_score:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      if (((int )SEQA[a_idx]) == ((int )SEQB[b_idx])) {
        M[a_str_idx + b_idx] = 1;
      }
       else {
        M[a_str_idx + b_idx] = -1;
      }
      ptr[a_str_idx + b_idx] = b_idx * 4;
    }
    M[a_str_idx + 5] = 0;
    alignedB[a_idx + 10] = '_';
  }
  alignedB[a_idx + 5] = '_';
}