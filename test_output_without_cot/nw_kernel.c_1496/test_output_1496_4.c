#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[256],char alignedB[256],int M[128][128],char ptr[16641])
{
  int r;
  int c;
  int _in_row;
  int _in_col;
  int a;
  int b;
  int score;
  int up_left;
  int up;
  int left;
  int max;
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_row:
  for (a = 0; a < 128; a++) {
    M[a][0] = a * -1;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_col:
  for (a = 0; a < 128; a++) {
    M[0][a] = a * -1;
  }
/* Matrix filling loop */
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  fill_out:
  for (b = 1; b < 128; b++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    fill_in:
    for (a = 1; a < 128; a++) {
      if (((int )SEQA[a - 1]) == ((int )SEQB[b - 1])) {
        score = 1;
      }
       else {
        score = -1;
      }
      up_left = M[a - 1][b - 1] + score;
      up = M[a - 1][b] - 1;
      left = M[a][b - 1] - 1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[a][b] = max;
/* Pointer tracking */
      
#pragma ACCEL POINT FACTOR=auto{__POINT__L3}
      if (max == left) {
        _in_row = a;
        _in_col = b - 1;
      }
      
#pragma ACCEL POINT FACTOR=auto{__POINT__L4}
      else {
        if (max == up) {
          _in_row = a - 1;
          _in_col = b;
        }
        
#pragma ACCEL POINT FACTOR=auto{__POINT__L5}
        else {
          _in_row = a - 1;
          _in_col = b - 1;
        }
      }
/* End of Pointer tracking */
    }
  }
/* TraceBack */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  trace:
  for (c = 16640; c >= 0; c--) {
    r = ptr[c];
    alignedA[c] = SEQA[r];
    alignedB[c] = SEQB[c - r];
  }
}