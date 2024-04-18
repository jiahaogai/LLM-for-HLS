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
    M[a_idx] = a_idx;
    ptr[a_idx] = -1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx;
    ptr[b_idx * 5] = -1;
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  loop_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    a_str_idx = a_idx * 5;
    row = M[a_str_idx];
    row_up = M[a_str_idx + 5];
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    loop_col:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      b_str_idx = b_idx * 5;
      left = M[b_str_idx];
      up_left = row_up + SEQA[b_str_idx];
      up = row + SEQB[b_str_idx];
      max = (up_left > up) ? (((up_left > left) ? a_idx * 5 + b_idx : a_idx * 5 + b_idx - 5)) : (((up > left) ? a_idx * 5 + b_idx + 5 : a_idx * 5 + b_idx));
      score = ((left > up) ? left : up);
      if (a_idx > 0 && b_idx > 0) {
        M[b_str_idx] = score;
        ptr[b_str_idx] = max;
      }
    }
    row = up;
    row_up = up_left;
  }
// TraceBack
  a_idx = 255;
  b_idx = 255;
  r = M[a_idx * 5 + b_idx];
  a_str_idx = a_idx * 5;
  b_str_idx = b_idx;
  alignedA[0] = SEQA[b_str_idx];
  alignedB[0] = SEQB[a_str_idx];
  
#pragma ACCEL PIPELINE auto{__PIPE__L4}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  trace:
  while (a_idx != 0 || b_idx != 0) {
    if (a_idx * 5 + b_idx == ptr[a_str_idx + b_idx]) {
      a_idx--;
      b_idx--;
      a_str_idx -= 5;
      b_str_idx--;
      alignedA[a_idx + 1] = alignedA[a_idx];
      alignedB[a_idx + 1] = alignedB[a_idx];
      alignedA[a_idx] = SEQA[b_str_idx];
      alignedB[a_idx] = SEQB[a_str_idx];
    }
    
#pragma ACCEL IF{__PARA__L5}
    else if (a_idx * 5 + b_idx == ptr[a_str_idx + b_idx + 1]) {
      a_idx--;
      b_str_idx++;
      alignedA[a_idx + 1] = alignedA[a_idx];
      alignedB[a_idx + 1] = alignedB[a_idx];
      alignedA[a_idx] = SEQA[b_str_idx];
    }
    
#pragma ACCEL ELSE{__PARA__L6}
    
#pragma ACCEL IF{__PARA__L7}
    else if (a_idx * 5 + b_idx == ptr[a_str_idx + b_idx - 1]) {
      a_idx--;
      b_idx++;
      b_str_idx--;
      alignedA[a_idx + 1] = alignedA[a_idx];
      alignedB[a_idx + 1] = alignedB[a_idx];
      alignedA[a_idx] = SEQA[b_str_idx];
    }
    
#pragma ACCEL ELSE{__PARA__L8}
    
#pragma ACCEL IF{__PARA__L9}
    else if (a_idx * 5 + b_idx == ptr[a_str_idx + b_idx + 5]) {
      a_idx++;
      b_idx--;
      a_str_idx += 5;
      b_str_idx--;
      alignedA[a_idx - 1] = alignedA[a_idx];
      alignedB[a_idx - 1] = alignedB[a_idx];
      alignedA[a_idx] = SEQA[b_str_idx];
    }
    
#pragma ACCEL ELSE{__PARA__L10}
    
#pragma ACCEL IF{__PARA__L11}
    else if (a_idx * 5 + b_idx == ptr[a_str_idx + b_idx + 6]) {
      a_idx++;
      b_str_idx++;
      alignedA[a_idx - 1] = alignedA[a_idx];
      alignedB[a_idx - 1] = alignedB[a_idx];
      alignedA[a_idx] = SEQA[b_str_idx];
    }
    
#pragma ACCEL ELSE{__PARA__L12}
    
#pragma ACCEL IF{__PARA__L13}
    else {
      a_idx++;
      b_idx++;
      a_str_idx += 5;
      b_str_idx++;
      alignedA[a_idx - 1] = alignedA[a_idx];
      alignedB[a_idx - 1] = alignedB[a_idx];
      alignedA[a_idx] = SEQA[b_str_idx];
      alignedB[a_idx] = SEQB[a_str_idx];
    }
  }
}