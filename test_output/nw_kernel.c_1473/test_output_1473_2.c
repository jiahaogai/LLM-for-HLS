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
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    M[a_idx] = a_idx;
    ptr[a_idx] = 0;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx;
    ptr[b_idx * 5] = 0;
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  fill_out:
  for (b_idx = 1; b_idx < 5; b_idx++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    fill_inner:
    for (a_idx = 1; a_idx < 5; a_idx++) {
      score = ((int )SEQA[b_idx * 5 + 5 - 1]) == ((int )SEQB[a_idx * 5 + 5 - 1]) ? 1 : ((int )0);
      up_left = M[(b_idx - 1) * 5 + (a_idx - 1)] + score;
      up = M[(b_idx - 1) * 5 + a_idx] + (-1);
      left = M[b_idx * 5 + (a_idx - 1)] + (-1);
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[b_idx * 5 + a_idx] = max;
      row_up = (b_idx - 1) * 5;
      if (max == left) {
        ptr[b_idx * 5 + a_idx] = 2 + row_up + a_idx;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      fill_diag:
      for (r = 1; r < 5; r++) {
        a_str_idx = a_idx * 5;
        b_str_idx = (b_idx - r) * 5;
        score = ((int )SEQA[b_str_idx + 5 - 1]) == ((int )SEQB[a_str_idx + 5 - 1]) ? 1 : ((int )0);
        up = M[b_str_idx + a_idx] + score;
        left = M[b_str_idx + (a_idx + 1)] + (-1);
        max = (up > left?up : left);
        M[b_str_idx + a_idx] = max;
        if (max == left) {
          ptr[b_str_idx + a_idx] = 1 + b_str_idx + a_idx;
        }
      }
    }
  }
// Traceback
  row = 4 * 5;
  a_idx = 4;
  b_idx = 4;
  a_str_idx = a_idx * 5;
  b_str_idx = b_idx * 5;
/*
    trace_out:
    while(a_idx != 0 || b_idx != 0){
      if(ptr[b_str_idx + a_idx] == 2 + row_up + a_idx){
        up_left = 1;
        a_idx--;
        b_idx--;
        b_str_idx -= 5;
      }
      else if(ptr[b_str_idx + a_idx] == row_up + a_idx){
        up = 1;
        a_idx--;
        b_str_idx -= 5;
      }
      else{
        left = 1;
        b_idx--;
        a_str_idx -= 5;
      }
      if(up_left){
        alignedA[a_idx] = '_';
        alignedB[b_idx] = '_';
      }
      else if(up){
        alignedA[a_idx] = '_';
        alignedB[b_idx] = SEQB[b_str_idx + 5 - 1];
      }
      else if(left){
        alignedA[a_idx] = SEQA[a_str_idx + 5 - 1];
        alignedB[b_idx] = '_';
      }
      else{
        alignedA[a_idx] = SEQA[a_str_idx + 5 - 1];
        alignedB[b_idx] = SEQB[b_str_idx + 5 - 1];
      }
    }
    alignedA[a_idx] = SEQA[a_str_idx + 5 - 1];
    alignedB[b_idx] = SEQB[b_str_idx + 5 - 1];
*/
}