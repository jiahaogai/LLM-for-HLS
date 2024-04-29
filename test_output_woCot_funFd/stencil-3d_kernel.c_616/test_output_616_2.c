#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
<<<<<<< HEAD
  long k_col;
  long j_col;
  long i_col;
  long buf[27];
=======
  long idx;
  long k_col;
  long j_col;
  long i_col;
  long k_row;
  long j_row;
  long i_row;
  long idxP;
  long idxM;
  long k_start;
  long k_end;
  long j_start;
  long j_end;
  long i_start;
  long i_end;
  long range;
  long ref;
  long k_step;
  long j_step;
  long i_step;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
<<<<<<< HEAD
/* Standardize from: for(k = 2; k < 39302; k++) {...} */
  for (k = 2; k <= ((long )39302) - 2; k++) {
=======
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  k_start = 1 + -3;
  k_end = 32 + 1 - 1;
  k_step = 1;
  if (k_start < 0) {
    k_start = 0;
  }
  if (k_end < 0) {
    k_end = 0;
  }
  if (k_step < 0) {
    range = 0 - k_start;
    k_step = 0 - k_step;
  }
  else {
    range = k_end - k_start;
  }
  range = (range + k_step - 1) / k_step;
  assert(range > 0);
  for (k = k_start, idx = 393216, k_col = 39304; k < k_end; k += k_step, idx += 8, k_col -= 1) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{30}
    loop_j:
<<<<<<< HEAD
/* Standardize from: for(j = 2; j < 39300; j++) {...} */
    for (j = 2; j <= ((long )39300) - 2; j++) {
=======
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    j_start = 1 + -3;
    j_end = 32 + 1 - 1;
    j_step = 1;
    if (j_start < 0) {
      j_start = 0;
    }
    if (j_end < 0) {
      j_end = 0;
    }
    if (j_step < 0) {
      range = 0 - j_start;
      j_step = 0 - j_step;
    }
    else {
      range = j_end - j_start;
    }
    range = (range + j_step - 1) / j_step;
    assert(range > 0);
    for (j = j_start, idxP = idx + 1, idxM = idx - 1, j_col = 39304 - 1; j < j_end; j += j_step, idxP += 8, idxM -= 8, j_col -= 1) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
<<<<<<< HEAD
/* Standardize from: for(i = 2; i < 39304; i++) {...} */
      for (i = 2; i <= 39304 - 2; i++) {
        k_col = ((k - 2) * 39300) + 2;
        j_col = ((j - 2) * 39304) + 2;
        i_col = ((i - 2) * 39304) + 2;
        buf[0] = orig[i_col - 2];
        buf[1] = orig[i_col - 1];
        buf[2] = orig[i_col];
        buf[3] = orig[i_col + 1];
        buf[4] = orig[i_col + 2];
        buf[5] = orig[i_col + 3];
        buf[6] = orig[i_col + 4];
        buf[7] = orig[i_col + 5];
        buf[8] = orig[i_col + 6];
        buf[9] = orig[i_col + 7];
        buf[10] = orig[i_col + 8];
        buf[11] = orig[i_col + 9];
        buf[12] = orig[i_col + 10];
        buf[13] = orig[i_col + 11];
        buf[14] = orig[i_col + 12];
        buf[15] = orig[i_col + 13];
        buf[16] = orig[i_col + 14];
        buf[17] = orig[i_col + 15];
        buf[18] = orig[i_col + 16];
        buf[19] = orig[i_col + 17];
        buf[20] = orig[i_col + 18];
        buf[21] = orig[i_col + 19];
        buf[22] = orig[i_col + 20];
        buf[23] = orig[i_col + 21];
        buf[24] = orig[i_col + 22];
        buf[25] = orig[i_col + 23];
        buf[26] = orig[i_col + 24];
        sol[k_col - 2] = ((C0 * buf[0]) + (C1 * buf[1])) + ((C0 * buf[2]) + (C1 * buf[3])) - sol[k_col - 2];
        sol[k_col - 1] = ((C0 * buf[1]) + (C1 * buf[2])) + ((C0 * buf[3]) + (C1 * buf[4])) - sol[k_col - 1];
        sol[k_col] = ((C0 * buf[2]) + (C1 * buf[3])) + ((C0 * buf[4]) + (C1 * buf[5])) - sol[k_col];
        sol[k_col + 1] = ((C0 * buf[3]) + (C1 * buf[4])) + ((C0 * buf[5]) + (C1 * buf[6])) - sol[k_col + 1];
        sol[k_col + 2] = ((C0 * buf[4]) + (C1 * buf[5])) + ((C0 * buf[6]) + (C1 * buf[7])) - sol[k_col + 2];
        sol[k_col + 3] = ((C0 * buf[5]) + (C1 * buf[6])) + ((C0 * buf[7]) + (C1 * buf[8])) - sol[k_col + 3];
        sol[k_col + 4] = ((C0 * buf[6]) + (C1 * buf[7])) + ((C0 * buf[8]) + (C1 * buf[9])) - sol[k_col + 4];
        sol[k_col + 5] = ((C0 * buf[7]) + (C1 * buf[8])) + ((C0 * buf[9]) + (C1 * buf[10])) - sol[k_col + 5];
        sol[k_col + 6] = ((C0 * buf[8]) + (C1 * buf[9])) + ((C0 * buf[10]) + (C1 * buf[11])) - sol[k_col + 6];
        sol[k_col + 7] = ((C0 * buf[9]) + (C1 * buf[10])) + ((C0 * buf[11]) + (C1 * buf[12])) - sol[k_col + 7];
        sol[k_col + 8] = ((C0 * buf[10]) + (C1 * buf[11])) + ((C0 * buf[12]) + (C1 * buf[13])) - sol[k_col + 8];
        sol[k_col + 9] = ((C0 * buf[11]) + (C1 * buf[12])) + ((C0 * buf[13]) + (C1 * buf[14])) - sol[k_col + 9];
        sol[k_col + 10] = ((C0 * buf[12]) + (C1 * buf[13])) + ((C0 * buf[14]) + (C1 * buf[15])) - sol[k_col + 10];
        sol[k_col + 11] = ((C0 * buf[13]) + (C1 * buf[14])) + ((C0 * buf[15]) + (C1 * buf[16])) - sol[k_col + 11];
        sol[k_col + 12] = ((C0 * buf[14]) + (C1 * buf[15])) + ((C0 * buf[16]) + (C1 * buf[17])) - sol[k_col + 12];
        sol[k_col + 13] = ((C0 * buf[15]) + (C1 * buf[16])) + ((C0 * buf[17]) + (C1 * buf[18])) - sol[k_col + 13];
        sol[k_col + 14] = ((C0 * buf[16]) + (C1 * buf[17])) + ((C0 * buf[18]) + (C1 * buf[19])) - sol[k_col + 14];
        sol[k_col + 15] = ((C0 * buf[17]) + (C1 * buf[18])) + ((C0 * buf[19]) + (C1 * buf[20])) - sol[k_col + 15];
        sol[k_col + 16] = ((C0 * buf[18]) + (C1 * buf[19])) + ((C0 * buf[20]) + (C1 * buf[21])) - sol[k_col + 16];
        sol[k_col + 17] = ((C0 * buf[19]) + (C1 * buf[20])) + ((C0 * buf[21]) + (C1 * buf[22])) - sol[k_col + 17];
        sol[k_col + 18] = ((C0 * buf[20]) + (C1 * buf[21])) + ((C0 * buf[22]) + (C1 * buf[23])) - sol[k_col + 18];
        sol[k_col + 19] = ((C0 * buf[21]) + (C1 * buf[22])) + ((C0 * buf[23]) + (C1 * buf[24])) - sol[k_col + 19];
        sol[k_col + 20] = ((C0 * buf[22]) + (C1 * buf[23])) + ((C0 * buf[24]) + (C1 * buf[25])) - sol[k_col + 20];
        sol[k_col + 21] = ((C0 * buf[23]) + (C1 * buf[24])) + ((C0 * buf[25]) + (C1 * buf[26])) - sol[k_col + 21];
        sol[k_col + 22] = ((C0 * buf[24]) + (C1 * buf[25])) + (C0 * buf[26]) - sol[k_col + 22];
      }
    }
  }
}
=======
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      i_start = 1 + -3;
      i_end = 32 + 1 - 1;
      i_step = 1;
      if (i_start < 0) {
        i_start = 0;
      }
      if (i_end < 0) {
        i_end = 0;
      }
      if (i_step < 0) {
        range = 0 - i_start;
        i_step = 0 - i_step;
      }
      else {
        range = i_end - i_start;
      }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
