#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[128],char alignedB[128])
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
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_row:
  for (a_idx = 0; a_idx < 128 + 1; a_idx++) {
    alignedA[a_idx] = ((char )0);
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_col:
  for (b_idx = 0; b_idx < 128 + 1; b_idx++) {
    alignedB[b_idx] = ((char )0);
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  fill_out:
  for (b_idx = 1; b_idx < 128 + 1; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    fill_in:
    for (a_idx = 1; a_idx < 128 + 1; a_idx++) {
      if (((int )SEQA[a_idx - 1]) == ((int )SEQB[b_idx - 1])) {
        score = 1;
      }
       else {
        score = -1;
      }
      row_up = (a_idx - 1) * (128 + 1);
      up_left = row_up + (b_idx - 1);
      up = row_up + b_idx;
      left = up_left + 1;
      max = ((int )alignedA[up_left]) + ((int )((char )'-'));
      
#pragma ACCEL PIPELINE auto{off}
      max = (((int )alignedA[up]) + ((int )((char )'-'))) > max ? ((int )alignedA[up]) + ((int )((char )'-')) : max;
      
#pragma ACCEL PIPELINE auto{off}
      max = (((int )alignedB[left]) + ((int )((char )'-'))) > max ? ((int )alignedB[left]) + ((int )((char )'-')) : max;
      
#pragma ACCEL PIPELINE auto{off}
      max = (((int )alignedA[left]) + ((int )SEQB[b_idx - 1])) > max ? ((int )alignedA[left]) + ((int )SEQB[b_idx - 1]) : max;
//#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
      for (r = 0; r < 32; r++) {
        row = r * (128 + 1);
        row_up = (a_idx - 1 - r) * (128 + 1);
        up_left = row_up + (b_idx - 1);
        up = row_up + b_idx;
        left = up_left + 1;
        a_str_idx = a_idx - 1 - r;
        b_str_idx = b_idx - 1;
//#pragma ACCEL PIPELINE auto{__PIPE__L3}
        
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
        
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
        score = ((int )alignedA[up_left]) + ((int )SEQB[b_str_idx]);
        if (score > ((int )alignedA[left]) + ((int )((char )'-'))) {
          score = ((int )alignedA[left]) + ((int )((char )'-'));
        }
        if (score > ((int )alignedA[up]) + ((int )((char )'-'))) {
          score = ((int )alignedA[up]) + ((int )((char )'-'));
        }
        alignedA[b_str_idx] = ((char )((int )((char )'A') + r));
//#pragma ACCEL PIPELINE auto{__PIPE__L4}
        
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
        
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
        score = ((int )alignedB[left]) + ((int )SEQA[a_str_idx]);
        if (score > ((int )alignedB[up_left]) + ((int )SEQA[a_str_idx])) {
          score = ((int )alignedB[up_left]) + ((int )SEQA[a_str_idx]);
        }
        if (score > ((int )alignedB[up]) + ((int )((char )'-'))) {
          score = ((int )alignedB[up]) + ((int )((char )'-'));
        }
        alignedB[a_str_idx] = ((char )((int )((char )'B') + r));
      }
    }
  }
// Traceback
  a_idx = 128;
  b_idx = 128;
  a_str_idx = a_idx;
  b_str_idx = b_idx;
/*
    trace_out:
    while(a_idx != 0 || b_idx != 0){
      row_up = (a_idx - 1) * (128 + 1);
      up_left = row_up + (b_idx - 1);
      up = row_up + b_idx;
      left = up_left + 1;
      if (((int )alignedA[up]) == ((int )alignedB[left])) {
        a_idx = a_idx - 1;
        b_idx = b_idx - 1;
        alignedA[a_str_idx] = SEQA[a_idx];
        alignedB[b_str_idx] = SEQB[b_idx];
        a_str_idx = a_idx;
        b_str_idx = b_idx;
      }
      else if (((int )alignedA[left]) == ((int )((char )'-'))) {
        a_idx = a_idx - 1;
        alignedA[a_str_idx] = SEQA[a_idx];
        alignedB[b_str_idx] = ((char )'-');
        b_str_idx = b_idx;
      }
      else if (((int )alignedB[up]) == ((int )((char )'-'))) {
        b_idx = b_idx - 1;
        alignedA[a_str_idx] = ((char )'-');
        alignedB[b_str_idx] = SEQB[b_idx];
        a_str_idx = a_idx;
      }
      else {
        a_idx = a_idx - 1;
        b_idx = b_idx - 1;
        alignedA[a_str_idx] = SEQA[a_idx];
        alignedB[b_str_idx] = SEQB[b_idx];
        a_str_idx = a_idx;
        b_str_idx = b_idx;
      }
    }
  }
*/
}