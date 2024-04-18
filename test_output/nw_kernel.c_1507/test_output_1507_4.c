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
  int a_idx_up;
  int b_idx_up;
  int a_idx_left;
  int b_idx_left;
  char a_char;
  char b_char;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    alignedA[a_idx] = ((char )0);
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    alignedB[b_idx] = ((char )0);
  }
// Matrix initialization
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  init_mat:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    init_arr:
    for (b_idx = 0; b_idx < 64; b_idx++) {
      if (a_idx == 0 && b_idx == 0) {
        M[0] = 0;
      }
      else if (a_idx == 0) {
        M[b_idx * 64] = ((int )('B' - 'A')) * (- 1);
        up_left = M[(b_idx - 1) * 64] + ((int )('B' - 'A')) * (- 1);
      }
      else if (b_idx == 0) {
        M[a_idx * 64] = ((int )('B' - 'A')) * (- 1);
        left = M[a_idx * 64 + 64] + ((int )('B' - 'A')) * (- 1);
      }
      else {
        M[b_idx * 64 + a_idx] = ((int )(SEQA[a_idx])) - ((int )(SEQB[b_idx])) + ((int )(alignedA[a_idx - 1])) + ((int )(alignedB[b_idx - 1]));
        up = M[b_idx * 64 + a_idx - 1] + ((int )('B' - 'A'));
        left = M[b_idx * 64 + a_idx - 1] + ((int )('B' - 'A'));
        up_left = M[(b_idx - 1) * 64 + a_idx - 1];
        max = (up_left > ((int )(left))) ? (up_left > ((int )(up))) ? up_left : ((int )(up)) : ((int )(left)) > ((int )(up)) ? ((int )(left)) : ((int )(up));
        score = M[b_idx * 64 + a_idx] - max;
      }
    }
  }
// TraceBack
  a_idx = 63;
  b_idx = 63;
  row = 64;
  r = 0;
  a_idx_up = a_idx - 1;
  b_idx_up = b_idx - 1;
  a_idx_left = a_idx - 1;
  b_idx_left = b_idx - 1;
/*
    traceBack:
    while (a_idx > 0 || b_idx > 0) {
      if (a_idx == 0) {
        a_char = '\0';
      }
      else {
        a_char = SEQA[a_idx - 1];
      }
  
      if (b_idx == 0) {
        b_char = '\0';
      }
      else {
        b_char = SEQB[b_idx - 1];
      }
  
      if (a_char == b_char) {
        row--;
        a_idx--;
        b_idx--;
        alignedA[r] = a_char;
        alignedB[r] = b_char;
        M[row] = 0;
      }
      else {
        if (((int )(alignedA[r])) == - 1) {
          a_idx = a_idx_left;
          b_idx = b_idx_left;
        }
        else {
          if (((int )(alignedB[r])) == - 1) {
            a_idx = a_idx_up;
            b_idx = b_idx_up;
          }
          else {
            row_up = (b_idx_up) * 64;
            left = M[row_up + a_idx] + ((int )('B' - 'A'));
            up = M[row + a_idx_left] + ((int )('B' - 'A'));
            up_left = M[row_up + a_idx_left];
            max = (up_left > ((int )(left))) ? (up_left > ((int )(up))) ? up_left : ((int )(up)) : ((int )(left)) > ((int )(up)) ? ((int )(left)) : ((int )(up));
            if (max == up_left) {
              a_idx = a_idx_left;
              b_idx = b_idx_left;
            }
            else {
              if (max == up) {
                a_idx = a_idx_up;
                b_idx = b_idx_up;
              }
              else {
                a_idx = a_idx_left;
                b_idx = b_idx_left;
              }
            }
          }
        }
        r++;
      }
    }
  }
*/
}