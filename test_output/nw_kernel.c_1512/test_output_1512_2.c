#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[130],char alignedB[130],int M[130][130],char ptr[130])
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
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = '-';
    M[a_idx][0] = ((int )a_idx) * ((int )'-');
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = '-';
    M[0][b_idx] = ((int )b_idx) * ((int )'-');
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  fill_out:
  for (b_idx = 1; b_idx < 5; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{128}
    fill_in:
    for (a_idx = 1; a_idx < 5; a_idx++) {
      if (((int )SEQA[a_idx - 1]) == ((int )SEQB[b_idx - 1])) {
        score = 1;
      }
       else {
        score = -1;
      }
      row_up = a_idx - 1;
      row = a_idx;
      up_left = M[row_up][b_idx - 1] + score;
      up = M[row_up][b_idx] - 1;
      left = M[row][b_idx - 1] - 1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[row][b_idx] = max;
      if (max == left) {
        ptr[b_idx] = ((char )60);
        a_str_idx = a_idx - 1;
        b_str_idx = b_idx - 1;
      }
       else {
        if (max == up) {
          ptr[b_idx] = ((char )94);
          a_str_idx = a_idx;
          b_str_idx = b_idx - 1;
        }
         else {
          ptr[b_idx] = ((char )92);
          a_str_idx = a_idx - 1;
          b_str_idx = b_idx;
        }
      }
      alignedA[(((int )'0') + a_idx)] = ((char )((int )SEQA[a_str_idx]));
      alignedB[(((int )'0') + b_idx)] = ((char )((int )SEQB[b_str_idx]));
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  r = 4;
  a_idx = 4;
  b_idx = 4;
  a_str_idx = a_idx - 1;
  b_str_idx = b_idx - 1;
  trace:
  while (1) {
    if ((int )ptr[b_idx] == 60) {
      alignedA[(((int )'0') + a_idx)] = ((char )((int )SEQA[a_str_idx]));
      alignedB[(((int )'0') + b_idx)] = ((char )((int )'~'));
      a_idx--;
      b_idx--;
      a_str_idx = a_idx - 1;
      b_str_idx = b_idx - 1;
    }
     else {
      if ((int )ptr[b_idx] == 94) {
        alignedA[(((int )'0') + a_idx)] = ((char )((int )'~'));
        alignedB[(((int )'0') + b_idx)] = ((char )((int )SEQB[b_str_idx]));
        b_idx--;
        b_str_idx = b_idx - 1;
      }
       else {
        alignedA[(((int )'0') + a_idx)] = ((char )((int )SEQA[a_str_idx]));
        alignedB[(((int )'0') + b_idx)] = ((char )((int )SEQB[b_str_idx]));
        a_idx--;
        b_idx--;
        a_str_idx = a_idx - 1;
        b_str_idx = b_idx - 1;
      }
    }
    if (a_idx == 0) {
      break;
    }
  }
}