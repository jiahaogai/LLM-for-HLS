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
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  init_mul:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    init_a:
    for (b_idx = 0; b_idx < a_idx; b_idx++) {
      M[a_idx * 5 + b_idx] = 0;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    init_b:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      if (b_idx < a_idx) {
        M[a_idx * 5 + b_idx] = 0;
      }
      else if (b_idx == a_idx) {
        M[a_idx * 5 + b_idx] = 0;
      }
      else {
        M[a_idx * 5 + b_idx] = ((int )SEQA[a_idx]) * ((int )SEQB[b_idx]) * SCORE_MATCH - SCORE_GAP_A * (a_idx) - SCORE_GAP_B * (b_idx);
      }
    }
  }
// Matrix multiplication
// A[x][y] = A[x][0] * B[0][y] + A[x][1] * B[1][y] + ... + A[x][y-1] * B[y-1][y]
  
#pragma ACCEL PIPELINE auto{__PIPE__L5}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
  mul_a:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L6}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
    mul_b:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      a_str_idx = 0;
      
#pragma ACCEL PIPELINE auto{__PIPE__L7}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
      score_a:
      for ( ; a_str_idx < a_idx; a_str_idx++) {
        b_str_idx = 0;
        
#pragma ACCEL PIPELINE auto{__PIPE__L8}
        
#pragma ACCEL TILE FACTOR=auto{__TILE__L8}
        
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
        score_b:
        for ( ; b_str_idx < b_idx; b_str_idx++) {
          up_left = M[a_str_idx * 5 + b_str_idx];
        }
        b_str_idx = 0;
        
#pragma ACCEL PIPELINE auto{__PIPE__L9}
        
#pragma ACCEL TILE FACTOR=auto{__TILE__L9}
        
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L9}
        score_eb:
        for ( ; b_str_idx < 5; b_str_idx++) {
          up = M[(a_str_idx ) * 5 + (b_idx ) + 1];
          left = M[(a_str_idx + 1) * 5 + (b_idx )];
          max = (up_left > ((up) > (left) ? (up) : (left))) ? up_left : ((up) > (left) ? (up) : (left));
          M[a_str_idx * 5 + b_idx] = max;
          ptr[a_str_idx * 5 + b_idx] = (int )(((up_left == max) ? 10 : ((up == max) ? 9 : 8)));
        }
      }
      a_str_idx = 0;
      
#pragma ACCEL PIPELINE auto{__PIPE__L10}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L10}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L10}
      score_last_a:
      for ( ; a_str_idx < 5 - 1; a_str_idx++) {
        b_str_idx = 5 - 1;
        
#pragma ACCEL PIPELINE auto{__PIPE__L11}
        
#pragma ACCEL TILE FACTOR=auto{__TILE__L11}
        
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L11}
        score_last_b:
        for ( ; b_str_idx > a_idx; b_str_idx--) {
          up_left = M[a_str_idx * 5 + b_str_idx];
        }
        b_str_idx = 5 - 1;
        
#pragma ACCEL PIPELINE auto{__PIPE__L12}
        
#pragma ACCEL TILE FACTOR=auto{__TILE__L12}
        
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L12}
        score_elb:
        for ( ; b_str_idx >= 0; b_str_idx--) {
          up = M[(a_str_idx ) * 5 + b_str_idx + 1];
          left = M[(a_str_idx + 1) * 5 + b_str_idx];
          max = (up_left > ((up) > (left) ? (up) : (left))) ? up_left : ((up) > (left) ? (up) : (left));
          M[a_str_idx * 5 + b_idx] = max;
          ptr[a_str_idx * 5 + b_idx] = (int )(((up_left == max) ? 10 : ((up == max) ? 9 : 8)));
        }