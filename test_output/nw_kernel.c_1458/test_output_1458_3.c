#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[128],char alignedB[128],int M[16641],char ptr[16641],int m,int n)
{
  int i;
  int j;
  int x;
  int y;
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
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_row:
  for (i = 0; i < 50; i++) {
    M[i] = i * - 1;
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  init_col:
  for (i = 0; i < 50; i++) {
    M[i * 50] = i * - 1;
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  loop_i:
  for (i = 1; i < 50 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    loop_j:
    for (j = 1; j < 50 - 1; j++) {
      score = ((int )SEQA[i * 50 - 1]) * ((int )SEQB[j * 50 - 1]) + ((int )SEQA[i * 50 - 1]) * 0 + ((int )SEQB[j * 50 - 1]) * 0;
      up_left = M[(i - 1) * 50 + (j - 1)] + ((int )SEQA[i * 50 - 1]) * ((int )SEQB[j * 50 - 1]) + 1;
      up = M[(i - 1) * 50 + j] + ((int )SEQA[i * 50 - 1]) * (- 1) + 1;
      left = M[i * 50 + (j - 1)] + ((int )SEQB[j * 50 - 1]) * (- 1) + 1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[i * 50 + j] = max;
      if (max == left) {
        ptr[i * 50 + j] = 2;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      loop_x:
      for (x = 0; x < 3; x++) {
        row_up = (i - 1) * 50 + j + x;
        row = i * 50 + j + x;
        a_idx = ((int )SEQA[row_up - 1]) - 65;
        b_idx = ((int )SEQB[row - 1]) - 65;
        score = ((int )SEQA[row_up - 1]) * ((int )SEQB[row - 1]) + a_idx * 0 + b_idx * 0;
        up_left = M[row_up] + a_idx * ((int )SEQB[row - 1]) + b_idx * 0;
        up = M[row] + a_idx * (- 1) + 1;
        left = M[row] + b_idx * (- 1) + 1;
        max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
        M[row] = max;
        if (max == left) {
          ptr[row] = 2;
        }
        
#pragma ACCEL PIPELINE auto{__PIPE__L4}
        
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
        
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
        loop_y:
        for (y = 0; y < 3; y++) {
          row_up = (i - 1) * 50 + j + x - 1;
          row = i * 50 + j + x - 1;
          a_idx = ((int )SEQA[row_up]) - 65;
          b_idx = ((int )SEQB[row]) - 65;
          score = ((int )SEQA[row_up]) * ((int )SEQB[row]) + a_idx * 0 + b_idx * 0;
          up_left = M[row_up + 1] + a_idx * ((int )SEQB[row + 1]) + b_idx * 0;
          up = M[row + 1] + a_idx * (- 1) + 1;
          left = M[row + 1] + b_idx * (- 1) + 1;
          max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
          M[row + 1] = max;
          if (max == left) {
            ptr[row + 1] = 2;
          }
        }
      }
    }
  }
// TraceBack
  i = 50 - 1;
  j = 50 - 1;
  a_idx = 0;
  b_idx = 0;
/*
    row_up = i*50 + j;
    row = i*50 + j + 1;
 */ 
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  trace:
  while (((int )SEQA[0]) != - 1) {
    if (ptr[j] == 0) {
      alignedA[a_idx++] = SEQA[i * 50 - 1];
      alignedB[b_idx++] = SEQB[j * 50 - 1];
      row_up = i * 50 + j;
      row = i * 50 + j + 1;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L5}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
    if (ptr[j] == 1) {
      alignedA[a_idx++] = SEQA[row_up - 1];
      alignedB[b_idx++] = SEQB[row - 1];
      i = row_up / 50;
      j = row_up - 50 * i;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L6}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
    if (ptr[j