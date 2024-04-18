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
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
    M[a_idx] = -a_idx - 1;
    ptr[a_idx] = 0;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
    M[b_idx] = -b_idx - 1;
    ptr[b_idx] = 0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  row_init:
  for (a_idx = 5; a_idx < 128 + 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx - 5];
    a_str_idx = (a_idx - 5) * 5;
    row_up = a_str_idx;
    row = a_str_idx + 5;
    score = ((int )alignedA[a_idx - 5]) && ((int )alignedB[0]);
    M[row_up] = -a_idx - 1;
    ptr[row_up] = 0;
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    col_init:
    for (b_idx = 5; b_idx < 128 + 5; b_idx++) {
      alignedB[b_idx] = SEQB[b_idx - 5];
      b_str_idx = (b_idx - 5) * 5;
      up_left = b_str_idx + a_idx - 5;
      left = b_str_idx + a_idx;
      if (a_idx == 5) {
        score = ((int )alignedA[a_idx - 5]) && ((int )alignedB[b_idx - 5]);
        M[left] = ((int )alignedB[b_idx - 5]) * 1;
        ptr[left] = 0;
      }
      
#pragma ACCEL IF(a_idx > 5)
      else {
        score = (((int )alignedA[a_idx - 5]) && ((int )alignedB[b_idx - 5])) + (((int )alignedA[a_idx - 4]) && ((int )alignedB[b_idx - 4])) - (((int )alignedA[a_idx - 5]) && ((int )alignedB[b_idx - 4]));
        M[left] = (((b_idx - 5) * 5) + (a_idx - 5)) + 1;
        if (score == M[up_left]) {
          ptr[left] = 2;
        }
        
#pragma ACCEL IF(score == M[up])
          else {
          if (score == M[left - 5]) {
            ptr[left] = 3;
          }
          
#pragma ACCEL ELSE
            else {
            if (score == M[up]) {
              ptr[left] = 1;
            }
            else {
              M[left] = score;
              ptr[left] = 0;
            }
            }
          }
        }
      }
    }
  }
  a_idx = 128 + 5;
  b_idx = 128 + 5;
  alignedA[a_idx] = 0;
  alignedB[b_idx] = 0;
}