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
  char a;
  char b;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    M[a_idx] = a_idx * - 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    M[b_idx * 64] = b_idx * - 1;
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  fill_out:
  for (b_idx = 1; b_idx < 63; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    fill_v:
    for (a_idx = 1; a_idx < 63; a_idx++) {
      a_str_idx = a_idx * 1 * 64;
      b_str_idx = b_idx * 1 * 64;
      a_str_idx_p1 = (a_idx + 1) * 1 * 64;
      b_str_idx_p1 = (b_idx + 1) * 1 * 64;
      a = ((SEQA[a_str_idx]) - 48);
      b = ((SEQB[b_str_idx]) - 48);
      score = ((SEQA[a_str_idx]) - 48) * ((SEQB[b_str_idx]) - 48);
      up_left = M[b_str_idx_p1 + a_idx_p1] + score;
      up = M[b_str_idx_p1 + a_idx] - 1;
      left = M[b_str_idx + a_str_idx_p1] - 1;
      if (up_left > ((up > left?up : left))){
        if (up_left > 0){
          max = up_left;
          row = b_idx_p1;
        }
        else {
          max = 0;
        }
      }
      else {
        if (up > left){
          max = up;
          row = b_idx_p1;
        }
        else {
          max = left;
          row = b_idx_p1 + 1;
        }
      }
      M[b_str_idx + a_str_idx] = max;
      if (max == left){
        ptr[b_str_idx + a_str_idx] = 2;
      }
      else {
        if (max == up){
          ptr[b_str_idx + a_str_idx] = 3;
        }
        else {
          ptr[b_str_idx + a_str_idx] = 1;
        }
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  row = 63;
  a_idx = 63;
  b_idx = 0;
  trace: while(a_idx || b_idx) {
    a_str_idx = a_idx * 1 * 64;
    b_str_idx = b_idx * 1 * 64;
    r = M[b_str_idx + a_str_idx];
    row_up = b_str_idx + a_idx_p1;
    if (r == M[row_up + a_str_idx]){
      a_idx -= 1;
      b_idx -= 1;
    }
    else {
      if (r == M[row_up + a_str_idx_p1]){
        a_idx -= 2;
        b_idx -= 1;
      }
      else {
        a_idx -= 1;
        b_idx -= 2;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  trace_out:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
    trace_v:
    for (a_idx = 0; a_idx < 64; a_idx++) {
      a_str_idx = a_idx * 1 * 64;
      b_str_idx = b_idx * 1 * 64;
      switch (ptr[b_str_idx + a_str_idx]) {
        case 0: 
          alignedA[a_idx] = '-';
          alignedB[b_idx] = SEQB[b_str_idx] ;
          break;
        case 1: 
          alignedA[a_idx] = SEQA[a_str_idx] ;
          alignedB[b_idx] = '-';
          break;
        case 2: 
          alignedA[a_idx] = SEQA[a_str_idx] ;
          alignedB[b_idx] = SEQB[b_str_idx] ;
          break;
        case 3: 
          alignedA[a_idx] = SEQA[a_str_idx] ;
          alignedB[b_idx] = SEQB[b_str_idx] ;
          break;
      }
    }
  }
}