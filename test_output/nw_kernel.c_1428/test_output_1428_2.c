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
    M[a_idx] = a_idx * -1;
    ptr[a_idx] = -1;
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx * -1;
    ptr[b_idx * 5] = -1;
  }
// Matrix multiplication loop
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  mul_blk:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    mul_seq:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      score = ((SEQA[a_idx] == SEQB[b_idx]) ? 1 : (-1));
      row_up = a_idx * 5;
      row = (a_idx + 1) * 5;
      up_left = M[row_up + b_idx] + score;
      up = M[row_up + b_idx + 1] + (-1);
      left = M[row + b_idx] + (-1);
      max = (up_left > ((up > left) ? (up) : (left)));
      M[row + b_idx + 1] = max;
      if (max == left) {
        ptr[row + b_idx + 1] = ((b_idx == 0) ? (-1) : (b_idx * 5 + ptr[row + b_idx - 1]));
      }
      else {
        if (max == up) {
          ptr[row + b_idx + 1] = ((b_idx == 0) ? ((-1) * 5) : (b_idx * 5 + ptr[row_up + b_idx - 1]));
        }
        else {
          ptr[row + b_idx + 1] = (b_idx * 5 + row_up + 1);
        }
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  a_idx = 4;
  b_idx = 4;
  a_str_idx = 255;
  b_str_idx = 255;
/*
    trace: while(a_idx != 0 || b_idx != 0) {
        r = b_idx*5 + a_idx;
        if (ptr[r] == -1){
            a_str[a_str_idx] = SEQA[a_idx];
            b_str[b_str_idx] = SEQB[b_idx];
            a_str_idx--;
            b_str_idx--;
            a_idx--;
            b_idx--;
        }
        else {
            if (ptr[r] == -5){
                a_str[a_str_idx] = SEQA[a_idx];
                b_str[b_str_idx] = '_';
                a_str_idx--;
                b_str_idx--;
                a_idx--;
            }
            else {
                if (ptr[r] % 5 == 0){
                    a_str[a_str_idx] = SEQA[a_idx];
                    b_str[b_str_idx] = '_';
                    a_str_idx--;
                    b_str_idx--;
                    a_idx--;
                }
                else {
                    if (ptr[r] == -4){
                        a_str[a_str_idx] = '_';
                        b_str[b_str_idx] = SEQB[b_idx];
                        a_str_idx--;
                        b_str_idx--;
                        b_idx--;
                    }
                    else {
                        if (ptr[r] == -3){
                            a_str[a_str_idx] = '_';
                            b_str[b_str_idx] = SEQB[b_idx];
                            a_str_idx--;
                            b_str_idx--;
                            b_idx--;
                            a_str[a_str_idx] = SEQA[a_idx];
                            b_str[b_str_idx] = '_';
                            a_str_idx--;
                            b_str_idx--;
                            a_idx--;
                        }
                        else {
                            if (ptr[r] == -2){
                                a_str[a_str_idx] = SEQA[a_idx];
                                b_str[b_str_idx] = '_';
                                a_str_idx--;
                                b_str_idx--;
                                a_idx--;
                                b_str[b_str_idx] = SEQB[b_idx];
                                b_str_idx--;
                                b_idx--;
                            }
                            else {
                                if (ptr[r] == -1){
                                    a_str[a_str_idx] = SEQA[a_idx];
                                    b_str[b_str_idx] = SEQB[b_idx];
                                    a_str_idx--;
                                    b_str_idx--;
                                    a_idx--;
                                    b_idx--;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    a_str[a_str_idx+1] = '\0';
    b_str[b_str_idx+1] = '\0';
*/
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  trace: while(a_idx != 0 || b_idx != 0) {
    r = b_idx * 5 + a_idx;
    if (ptr[r] == -1) {
      a_str[a_str_idx--] = SEQA[a_idx];
      b_str[b_str_idx--] = SEQB[b_idx];
      a_idx--;
      b_idx--;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    trace_up:
    for (; ; ) {
      if (ptr[r] == -5) {
        a_str[a_str_idx--] = SEQA[a_idx];
        b_str[b_str_idx--] = '_';
        a_idx--;
      }