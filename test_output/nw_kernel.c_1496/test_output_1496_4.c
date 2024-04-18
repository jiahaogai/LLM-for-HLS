#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[256],char alignedB[256],int M[166],char ptr[16641])
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
  int score_row;
  int u;
  int _in_x;
  int _in_y;
  int _out_y;
  int _out_x;
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  fill_out:
  for (b_idx = 5; b_idx < 250; b_idx++) {
    alignedB[b_idx] = '_';
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  fill_out_row:
  for (a_idx = 5; a_idx < 250; a_idx++) {
    alignedA[a_idx] = '_';
    b_str_idx = 0;
    score_row = (a_idx * 5) + 5;
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    fill_out_col:
    for (b_idx = 5; b_idx < 250; b_idx++) {
      a_str_idx = 0 + 4 * a_idx;
      if (((int )SEQA[a_str_idx]) == ((int )SEQB[b_str_idx])) {
        score = 1;
      }
       else {
        score = 0;
      }
      up_left = M[score_row + 4] + score;
      up = M[score_row + 4 + 5] + (- 1);
      left = M[score_row + 0] + (- 1);
      max = up_left;
      
#pragma ACCEL CONDITION = auto{__PARA__L3_0}
      if (up > max) {
        max = up;
      }
      
#pragma ACCEL CONDITION = auto{__PARA__L3_1}
      if (left > max) {
        max = left;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      fill_diag:
      for (u = 1; u < 5; u++) {
        row_up = score_row + 4 - u;
        row = score_row + 4 + u;
        if (((int )SEQA[a_str_idx]) == ((int )SEQB[b_str_idx + u])) {
          score = 1;
        }
         else {
          score = 0;
        }
        up_left = M[row_up] + score;
        up = M[row] + (- 1);
        left = M[row_up + 5] + (- 1);
        M[row] = left;
        ptr[row] = ((b_str_idx + u) << 16) | (a_str_idx);
//#pragma ACCEL PIPELINE auto{__PIPE__L4}
//#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
      }
//#pragma ACCEL PIPELINE auto{__PIPE__L3}
    }
//#pragma ACCEL PIPELINE auto{__PIPE__L3}
  }
//#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  trace_back:
  for (_out_y = 5; _out_y < 250; _out_y++) {
    b_str_idx = (_out_y * 5) + 5;
    a_str_idx = (ptr[_out_y] >> 16) * 5;
    alignedA[_out_y] = SEQA[a_str_idx];
    alignedB[_out_y] = SEQB[b_str_idx];
    _in_y = _out_y;
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
    trace_back_row:
    while (a_str_idx > 0) {
      b_str_idx = (ptr[_in_y] >> 16) * 5;
      if (a_str_idx != ((int )alignedA[_in_y])) {
        a_str_idx = (ptr[_in_y] >> 16);
        alignedA[_in_y] = SEQA[a_str_idx];
      }
       else {
        a_str_idx = 0;
      }
      if (b_str_idx != ((int )alignedB[_in_y])) {
        b_str_idx = ptr[_in_y] & 0xffff;
        alignedB[_in_y] = SEQB[b_str_idx];
      }
       else {
        b_str_idx = 0;
      }
      _in_x = _in_y;
      _in_y = ((int )ptr[_in_y]) >> 16;
    }
  }
}