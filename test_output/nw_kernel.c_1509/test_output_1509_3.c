c
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
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  init_main:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    init_col_j:
    for (a_idx = 0; a_idx < 5; a_idx++) {
      if (((int )alignedA[a_idx]) == ((int )alignedB[b_idx])) {
        M[0] = 1;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L5}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
      init_row_i:
      for (r = 1; r < 5; r++) {
        a_str_idx = a_idx + (r * 5);
        b_str_idx = b_idx + (r * 1);
        up_left = M[(r - 1) * 5 + (a_idx - 1)];
        up = M[(r - 1) * 5 + a_idx];
        left = M[r * 5 + (a_idx - 1)];
        score = ((int )alignedA[a_str_idx]) == ((int )alignedB[b_str_idx])?1:-1;
        max = (up_left > ((up > left)?up:left))?up_left:((up > left)?up:left);
        M[r * 5 + a_idx] = ((int )alignedA[a_str_idx]) == ((int )alignedB[b_str_idx])?max + score:max;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L6}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
  track:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
    track_j:
    for (a_idx = 0; a_idx < 5; a_idx++) {
      row = 5 - 1;
      row_up = ((int )alignedA[a_idx + ((5 - 1) * 5)]) == ((int )alignedB[b_idx + ((5 - 1) * 1)])?1:-1;
      
#pragma ACCEL PIPELINE auto{__PIPE__L9}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L9}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L10}
      track_i:
      for (i = 5 - 2; i >= 0; i--) {
        a_str_idx = a_idx + (i * 5);
        b_str_idx = b_idx + (i * 1);
        up = M[(i + 1) * 5 + a_idx] + row_up;
        left = M[i * 5 + a_idx + 1] + M[i * 5 + a_idx];
        row_up = M[i * 5 + a_idx] + score;
        score = ((int )alignedA[a_str_idx]) == ((int )alignedB[b_str_idx])?1:-1;
        max = (up > left)?up:left;
        max = (row_up > max)?row_up:max;
        M[i * 5 + a_idx] = max;
        if (max == left) {
          ptr[i * 5 + a_idx] = 3;
        }
        
#pragma ACCEL PIPELINE auto{__PIPE__L11}
        if (max == up) {
          ptr[i * 5 + a_idx] = 2;
        }
        
#pragma ACCEL PIPELINE auto{__PIPE__L12}
        if (max == row_up) {
          ptr[i * 5 + a_idx] = 1;
        }
      }
      row = 0;
    }
  }
}