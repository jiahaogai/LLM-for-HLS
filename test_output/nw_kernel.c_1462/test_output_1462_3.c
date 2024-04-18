#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[128],char alignedB[128],char ptr[128],int M[128])
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
  int i;
  int j;
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    M[a_idx] = a_idx * (-1);
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 16] = b_idx * (-1);
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  fill_out:
  for (a_idx = 1; a_idx < 15; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{128}
    fill_in_a:
    for (a_str_idx = 0; a_str_idx < 16; a_str_idx++) {
      alignedA[a_str_idx] = ((a_idx - 1) * 16 + a_str_idx < 128) ? SEQA[((a_idx - 1) * 16 + a_str_idx)] : ((char )0);
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    fill_in_b:
    for (b_idx = 1; b_idx < 6; b_idx++) {
      alignedB[b_idx * 16] = ((b_idx - 1) * 16 + 0 < 128) ? SEQB[((b_idx - 1) * 16)] : ((char )0);
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      fill_in_c:
      for (b_str_idx = 1; b_str_idx < 16; b_str_idx++) {
        a_str_idx = 0 + 1 * b_str_idx;
        score = ((int )alignedA[a_str_idx + 0]) * ((int )alignedB[b_str_idx + 0]) + ((int )alignedA[a_str_idx + 1]) * ((int )alignedB[b_str_idx + 1]) + ((int )alignedA[a_str_idx + 2]) * ((int )alignedB[b_str_idx + 2]) + ((int )alignedA[a_str_idx + 3]) * ((int )alignedB[b_str_idx + 3]) + ((int )alignedA[a_str_idx + 4]) * ((int )alignedB[b_str_idx + 4]) + ((int )alignedA[a_str_idx + 5]) * ((int )alignedB[b_str_idx + 5]) + ((int )alignedA[a_str_idx + 6]) * ((int )alignedB[b_str_idx + 6]) + ((int )alignedA[a_str_idx + 7]) * ((int )alignedB[b_str_idx + 7]) + ((int )alignedA[a_str_idx + 8]) * ((int )alignedB[b_str_idx + 8]) + ((int )alignedA[a_str_idx + 9]) * ((int )alignedB[b_str_idx + 9]) + ((int )alignedA[a_str_idx + 10]) * ((int )alignedB[b_str_idx + 10]) + ((int )alignedA[a_str_idx + 11]) * ((int )alignedB[b_str_idx + 11]) + ((int )alignedA[a_str_idx + 12]) * ((int )alignedB[b_str_idx + 12]) + ((int )alignedA[a_str_idx + 13]) * ((int )alignedB[b_str_idx + 13]) + ((int )alignedA[a_str_idx + 14]) * ((int )alignedB[b_str_idx + 14]) + ((int )alignedA[a_str_idx + 15]) * ((int )alignedB[b_str_idx + 15]);
        row = b_idx * 16;
        row_up = (b_idx - 1) * 16;
        up_left = M[row_up + 0] + ((int )alignedA[0] * ((int )alignedB[b_str_idx + 0]));
        up = M[row_up + b_str_idx] + ((int )alignedA[0] * ((int )alignedB[b_str_idx]));
        left = M[row + 0 + a_str_idx] + ((int )alignedB[b_str_idx + 0] * ((int )alignedA[a_str_idx]));
        max = (up_left > up ? up_left : up);
        max = (max > left ? max : left);
        M[row + a_str_idx] = max;
        ptr[row + a_str_idx] = ((max == left) ? 2 : ((max == up_left) ? 3 : 1));
      }
    }
  }
// TraceBack
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
  trace:
  for (a_idx = 5 - 1; a_idx >= 0; a_idx--) {
    i = a_idx * 16;
    j = 16 - 1;
    r = i + j;
    a_str_idx = 0 + 1 * j;
    b_str_idx = 0 + 1 * i;
    score = M[r];
    while (a_str_idx > 0 || b_str_idx > 0) {
      if (ptr[r] == 1) {
        a_str_idx -= 1;
        b_str_idx -= 1;
        r = i + b_str_idx;
        score = M[r] + ((int )alignedA[a_str_idx] * ((int )alignedB[b_str_idx]));
      }
      else if (ptr[r] == 2) {
        a_str_idx -= 1;
        r = i + b_str_idx;
        score = M[r] + ((int )alignedA[a_str_idx] * ((int )alignedB[b_str_idx]));
      }
      else if (ptr[r] == 3) {
        b_str_idx -= 1;
        r = i + b_str_idx;
        score = M[r] + ((int )alignedA[a_str_idx] * ((int )alignedB[b_str_idx]));
      }
    }
  }
}