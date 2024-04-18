#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[128],char alignedB[128],int M[16641],char ptr[16641])
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
    M[a_idx] = a_idx * - 1;
    ptr[a_idx] = 0;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx * - 1;
    ptr[b_idx * 5] = 0;
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  loop_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    loop_col:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      score = ((SEQA[a_idx] == SEQB[b_idx]) ? 1 : - 1);
      row_up = a_idx * 5;
      up_left = row_up + b_idx;
      up = row_up + 5;
      left = up_left + 1;
      max = M[up_left] + score;
      if (a_idx > 0) {
        max = (M[up] > max) ? M[up] : max;
      }
      if (b_idx > 0) {
        max = (M[left] > max) ? M[left] : max;
      }
      M[a_idx * 5 + b_idx] = max;
      ptr[a_idx * 5 + b_idx] = ((M[a_idx * 5 + b_idx] == ((M[up_left] + - 1)) ? 7 : ((M[a_idx * 5 + b_idx] == ((M[up] + - 1)) ? 6 : ((M[a_idx * 5 + b_idx] == ((M[left] + - 1)) ? 5 : ((M[a_idx * 5 + b_idx] == ((M[up_left] + 1)) ? 0 : ((M[a_idx * 5 + b_idx] == ((M[up] + 1)) ? 1 : ((M[a_idx * 5 + b_idx] == ((M[left] + 1)) ? 2 : 3)))))))))));
    }
  }
// TraceBack
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
  row = 4;
  b_idx = 4;
  a_str_idx = 0;
  b_str_idx = 0;
/*
    row = 4
    b_idx = 4
    a_str_idx = 0
    b_str_idx = 0
    score =  (SEQA[a_idx] == SEQB[b_idx])? 1 : -1
    up_left = a_idx*5 + b_idx
    up = a_idx*5 + 5
    left = up_left + 1
    max =  M[up_left] + score
    if (a_idx > 0) {
      max =  (M[up] > max)? M[up] : max
    }
    if (b_idx > 0) {
      max =  (M[left] > max)? M[left] : max
    }
    M[a_idx*5+b_idx] = max
    ptr[a_idx*5+b_idx] =  (M[a_idx*5+b_idx] == (M[up_left] + - 1))? 7 :  (M[a_idx*5+b_idx] == (M[up] + - 1))? 6 :  (M[a_idx*5+b_idx] == (M[left] + - 1))? 5 :  (M[a_idx*5+b_idx] == (M[up_left] + 1))? 0 :  (M[a_idx*5+b_idx] == (M[up] + 1))? 1 :  (M[a_idx*5+b_idx] == (M[left] + 1))? 2 : 3
    if (M[a_idx*5+b_idx] == 0) {
      a_idx = a_idx + 1
      b_idx = b_idx + 1
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L7}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
    loop_lbl7:
    while(1) {
      if (a_idx <= 0 || b_idx <= 0) {
        break;
      }
      if (ptr[a_idx*5+b_idx] == 0) {
        a_idx = a_idx + 1;
        b_idx = b_idx + 1;
      }
      else {
        if (ptr[a_idx*5+b_idx] == 1) {
          a_idx = a_idx + 1;
        }
        else {
          if (ptr[a_idx*5+b_idx] == 2) {
            b_idx = b_idx + 1;
          }
          else {
            if (ptr[a_idx*5+b_idx] == 3) {
              a_idx = a_idx + 1;
              b_idx = b_idx + 1;
            }
            else {
              if (ptr[a_idx*5+b_idx] == 5) {
                a_idx = a_idx + 1;
                b_idx = b_idx - 1;
              }
              else {
                if (ptr[a_idx*5+b_idx] == 6) {
                  a_idx = a_idx - 1;
                  b_idx = b_idx + 1;
                }
                else {
                  a_idx = a_idx - 1;
                  b_idx = b_idx - 1;
                }
              }
            }
          }
        }
      }
      score = ((SEQA[a_idx] == SEQB[b_idx]) ? 1 : - 1);
      row_up = a_idx * 5;
      up_left = row_up + b_idx;
      up = row_up + 5;
      left = up_left + 1;
      max = M[up_left] + score;
      if (a_idx > 0) {
        max = (M[up] > max) ? M[up] : max;
      }
      if (b_idx > 0) {
        max = (M[left] > max) ? M[left] : max;
      }
      M[a_idx * 5 + b_idx] = max;
      ptr