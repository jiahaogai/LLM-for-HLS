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
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
  }
  alignedA[5] = (char )'\0';
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  alignedB[5] = (char )'\0';
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  init_mat:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    init_mat_row:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      if (a_idx == 0 && b_idx == 0) {
        M[0] = 0;
      }
      else if (a_idx == 0) {
        M[b_idx * 6] = ((int )'B') - ((int )'A') - 1;
        score = ((int )SEQB[b_idx]) - ((int )'A') - 1;
        M[b_idx * 6] += score;
      }
      else if (b_idx == 0) {
        M[a_idx * 6] = ((int )'A') - ((int )'B') - 1;
        score = ((int )SEQA[a_idx]) - ((int )'B') - 1;
        M[a_idx * 6] += score;
      }
      else {
        row_up = a_idx * 6;
        up_left = row_up + (b_idx - 1);
        up = row_up + b_idx;
        left = up - 6;
        M[up] = ((int )SEQA[a_idx]) - ((int )SEQB[b_idx]) - 1 + ((int ) )((bool )(M[left] > M[up_left]) ? M[left] : ((bool )(M[up_left] > M[up]) ? M[up_left] : M[up])));
      }
    }
  }
}