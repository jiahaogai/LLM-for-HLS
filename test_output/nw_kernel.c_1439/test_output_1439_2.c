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
  int index;
  int last_row_idx;
  int last_a_idx;
  int last_b_idx;
  int a_str_idx_base;
  int b_str_idx_base;
  int a_row_end;
  int b_row_end;
  int a_row_no_padding_end;
  int b_row_no_padding_end;
  int pad_a;
  int pad_b;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    alignedA[a_idx] = ((char )0);
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    alignedB[b_idx] = ((char )0);
  }
/* Row initialization */
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  init_row_in_A:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
  }
/* Column initialization */
  
#pragma ACCEL PIPELINE auto{__PIPE__L4}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
  init_col_in_B:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
  }
/* Matrix initialization */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
  fill_in:
  for (a_idx = 1; a_idx < 64; a_idx++) {
    a_str_idx_base = (a_idx << 6);
    pad_a = 0;
    if (a_str_idx_base < 8) {
      pad_a = 8 - a_str_idx_base;
    }
    a_row_end = (a_str_idx_base + 8);
    if (a_row_end > 64) {
      a_row_end = 64;
    }
    a_row_no_padding_end = (a_str_idx_base + 8) - pad_a;
    b_str_idx_base = 0;
    pad_b = 0;
    if (b_str_idx_base < 8) {
      pad_b = 8 - b_str_idx_base;
    }
    b_row_end = (b_str_idx_base + 8);
    if (b_row_end > 64) {
      b_row_end = 64;
    }
    b_row_no_padding_end = (b_str_idx_base + 8) - pad_b;
    row:
    for (a_str_idx = pad_a; a_str_idx < a_row_no_padding_end; a_str_idx++) {
      b_str_idx = pad_b;
      row_b:
      for (b_str_idx = pad_b; b_str_idx < b_row_no_padding_end; b_str_idx++) {
        if (a_str_idx == pad_a) {
          if (b_str_idx == pad_b) {
            M[0] = 0;
          }
          else {
            M[b_str_idx] = ((int )(alignedB[b_str_idx] - 32)) * ((int )(alignedB[b_str_idx] - 32)) + ((int )(alignedB[b_str_idx] - 32)) * 1;
          }
        }
        else if (b_str_idx == pad_b) {
          M[a_str_idx * 64] = ((int )(alignedA[a_str_idx] - 32)) * ((int )(alignedA[a_str_idx] - 32)) + ((int )(alignedA[a_str_idx] - 32)) * 1;
        }
        else {
          up_left = M[(a_str_idx - 1) * 64 + (b_str_idx - 1)];
          up = M[(a_str_idx - 1) * 64 + b_str_idx];
          left = M[a_str_idx * 64 + (b_str_idx - 1)];
          score = (up_left + ((int )(alignedA[a_str_idx] - 32) * (int )(alignedB[b_str_idx] - 32)));
          max = (up > left)?up:left;
          max = (score > max)?score:max;
          score = (left + ((int )(alignedA[a_str_idx] - 32) * (int )(alignedB[b_str_idx + 1] - 32)));
          max = (score > max)?score:max;
          score = (up + ((int )(alignedA[a_str_idx + 1] - 32) * (int )(alignedB[b_str_idx] - 32)));
          max = (score > max)?score:max;
          M[a_str_idx * 64 + b_str_idx] = max;
          ptr[a_str_idx * 64 + b_str_idx] = ((char )(max > 0?(((up_left > max)?((int )0) : ((int )1))) : ((int )2)));
        }
      }
    }
  }
/* TraceBack */
  last_row_idx = 63;
  last_a_idx = 63;
  last_b_idx = 63;
  a_str_idx_base = 63 << 6;
  b_str_idx_base = 63;
  a_row_end = a_str_idx_base + 8;
  b_row_end = b_str_idx_base + 8;
  pad_a = 0;
  pad_b = 0;
  if (a_str_idx_base < 8) {
    pad_a = 8 - a_str_idx_base;
  }
  if (b_str_idx_base < 8) {
    pad_b = 8 - b_str_idx_base;
  }
  a_row_no_padding_end = a_str_idx_base + 8 - pad_a;
  b_row_no_padding_end = b_str_idx_base + 8 - pad_b;
/* Pad A */
  trace_pad_a_in:
  for (i = 0; i < pad_a; i++) {
    trace_pad_a[i] = trace_pad_a[pad_a - 1];
  }
/* Pad B */
  trace_pad