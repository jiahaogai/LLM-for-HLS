#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[256],char alignedB[256],char score_matrix[256][256],int M[128+1][128+1],int ptr[256][256],int m,int n)
{
  int i;
  int j;
  int score;
  int up_left;
  int up;
  int left;
  int max;
  int row;
  int row_up;
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  init_row:
  for (i = 0; i < 128 + 1; i++) {
    M[i][0] = i * -1;
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  init_col:
  for (i = 0; i < 128 + 1; i++) {
    M[0][i] = i * -1;
  }
/* Matrix filling loop */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  fill_out:
  for (i = 1; i < 128 + 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    fill_in:
    for (j = 1; j < 128 + 1; j++) {
      if (((int )SEQA[i - 1]) == ((int )SEQB[j - 1])) {
        score = 1;
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
      up_left = M[i - 1][j - 1] + score;
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
      up = M[i - 1][j] - 1;
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      left = M[i][j - 1] - 1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[i][j] = max;
      if (max == left) {
        ptr[i][j] = 2;
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      if (max == up) {
        ptr[i][j] = 1;
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      if (max == up_left) {
        ptr[i][j] = 0;
      }
    }
  }
/* TraceBack */
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
  row = m + n;
  row_up = m + n - 1;
  alignedA[row] = '\0';
  alignedB[row] = '\0';
  
#pragma ACCEL PIPELINE auto{__PIPE__L7}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
  trace:
  while (row > 0) {
    i = 0;
    j = 0;
    score = M[i][j];
    row_up = row - 1;
    if (ptr[row][j] == 2) {
      alignedA[row_up] = SEQA[i];
      alignedB[row_up] = SEQB[j];
      i++;
      j++;
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
    up:
    while (ptr[row][j] == 1) {
      alignedA[row_up] = SEQA[i];
      alignedB[row_up] = SEQB[j];
      i++;
      j++;
      score = M[i][j];
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L9}
    left:
    while (ptr[row][j] == 0) {
      alignedA[row_up] = SEQA[i];
      alignedB[row_up] = SEQB[j];
      j++;
      score = M[i][j];
    }
  }
}