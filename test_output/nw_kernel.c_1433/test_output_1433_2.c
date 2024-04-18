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
  int a_row_end;
  int a_row_start;
  int b_row_end;
  int b_row_start;
  int a_col_end;
  int a_col_start;
  int b_col_end;
  int b_col_start;
  int a_temp;
  int b_temp;
  int m_row_end;
  int m_row_start;
  int p_row_end;
  int p_row_start;
  int pad_a;
  int pad_b;
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_A:
  for (a_idx = 0; a_idx < 128; a_idx++) {
    SEQA[a_idx] = 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_B:
  for (b_idx = 0; b_idx < 128; b_idx++) {
    SEQB[b_idx] = 2;
  }
/* Pad A and B */
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  pad_a = 15;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  pad_b = 14;
  a_row_end = 16;
  a_row_start = 1;
  b_row_end = 16;
  b_row_start = 1;
  a_col_end = 16;
  a_col_start = 15;
  b_col_end = 16;
  b_col_start = 14
  pad_row_a:
  for (a_idx = 0; a_idx < a_row_start; a_idx++) {
    a_temp = 0;
    pad_col_a:
    for (b_idx = 0; b_idx < 16; b_idx++) {
      alignedA[a_idx * 16 + b_idx] = a_temp;
    }
  }
  pad_row_a_end:
  for (a_idx = a_row_end; a_idx < 16; a_idx++) {
    a_temp = 0;
    pad_col_a:
    for (b_idx = 0; b_idx < 16; b_idx++) {
      alignedA[a_idx * 16 + b_idx] = a_temp;
    }
  }
  pad_row_b:
  for (a_idx = a_row_start; a_idx < a_row_end; a_idx++) {
    a_temp = SEQA[a_idx];
    pad_col_b:
    for (b_idx = 0; b_idx < b_col_start; b_idx++) {
      alignedB[a_idx * 16 + b_idx] = a_temp;
    }
  }
  pad_row_b_end:
  for (a_idx = a_row_start; a_idx < a_row_end; a_idx++) {
    a_temp = SEQA[a_idx];
    pad_col_b:
    for (b_idx = b_col_end; b_idx < 16; b_idx++) {
      alignedB[a_idx * 16 + b_idx] = a_temp;
    }
  }
  main_row_a:
  for (a_idx = a_row_start; a_idx < a_row_end; a_idx++) {
    a_temp = SEQA[a_idx];
    main_col_b:
    for (b_idx = b_col_start; b_idx < b_col_end; b_idx++) {
      b_temp = SEQB[b_idx];
      score = (a_temp == b_temp) ? 1LL : -1LL;
      m_row_end = ((a_idx + 1) == 15) ? 16 : (a_idx + 1);
      m_row_start = ((a_idx - 1) == 0) ? 1 : (a_idx - 1);
      p_row_end = ((a_idx + 1) == 15) ? a_idx : (a_idx + 1);
      p_row_start = ((a_idx - 1) == 0) ? a_idx : (a_idx - 1);
      row = (a_idx * 16) + b_idx;
      up_left = M[(p_row_start * 16) + b_col_start] + score;
      up = M[(p_row_start * 16) + b_idx] - 1LL;
      left = M[(a_idx * 16) + b_col_start] - 1LL;
      max = (up_left > ((up > left) ? up : left)) ? up_left : ((up > left) ? up : left);
      M[row] = max;
      if (max == left) {
        ptr[row] = 2;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
      down_a:
      for (r = m_row_start + 1; r < m_row_end; r++) {
        row_up = (r * 16) + b_idx;
        row = (a_idx * 16) + b_idx;
        up_left = M[row_up] + ((a_temp == b_temp) ? 1LL : -1LL);
        up = M[row_up] - 1LL;
        left = M[row] - 1LL;
        max = (up_left > ((up > left) ? up : left)) ? up_left : ((up > left) ? up : left);
        M[row] = max;
        if (max == left) {
          ptr[row] = 0;
        }
        
#pragma ACCEL PIPELINE auto{__PIPE__L3}
        
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
        
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
        down_b:
        for (int _in_idx = 0; _in_idx < 16; _in_idx++) {
          b_idx = b_col_start + _in_idx;
          row_up = (r * 16) + b_idx;
          row = (a_idx * 16) + b_idx;
          up_left = M[row_up] + ((a_temp == b_temp) ? 1LL : -1LL);
          up = M[row_up] - 1LL;
          left = M[row] - 1LL;
          max = (up_left > ((up > left) ? up : left)) ? up_left : ((up > left) ? up : left);
          M[row] = max;
          if (max == left) {
            ptr[row] = 3;
          }
        }
      }
    }
  }
/* TraceBack */
  a_idx = 15;
  b_idx = 15;
  row = (a_idx * 1