#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long m;
  long n;
  long o;
  long P[8];
  long M[8];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 32 + 1 - 8;j++) {...} */
  for (j = 1 + 8;j < 32 + 1;j++) {
     P[0] = orig[0 + 3904 * (j - 1)];
     P[1] = orig[1 + 3904 * (j - 1)];
     P[2] = orig[2 + 3904 * (j - 1)];
     P[3] = orig[3904 + 3904 * (j - 1)];
     P[4] = orig[4 + 3904 * (j - 1)];
     P[5] = orig[5 + 3904 * (j - 1)];
     P[6] = orig[6 + 3904 * (j - 1)];
     P[7] = orig[7 + 3904 * (j - 1)];
     loopk:
/* Standardize from: for(k = 1;k < 32 + 1 - 8;k++) {...} */
     for (k = 1 + 8;k < 32 + 1;k++) {
       idx = 3904 * (k - 1) + 1;
       M[0] = P[0];
       M[1] = P[1];
       M[2] = P[2];
       M[3] = P[3];
       M[4] = P[4];
       M[5] = P[5];
       M[6] = P[6];
       M[7] = P[7];
       P[0] = P[8];
       P[1] = P[9];
       P[2] = P[10];
       P[3] = P[11];
       P[4] = P[12];
       P[5] = P[13];
       P[6] = P[14];
       P[7] = P[15];
       M[8] = P[16];
       M[9] = P[17];
       M[10] = P[18];
       M[11] = P[19];
       M[12] = P[20];
       M[13] = P[21];
       M[14] = P[22];
       M[15] = P[23];
       sol[idx] = ((C0 * M[0]) + (C1 * M[1]));
       sol[idx + 1] = ((C0 * M[1]) + (C1 * M[2]));
       sol[idx + 2] = ((C0 * M[2]) + (C1 * M[3]));
       sol[idx + 3904] = ((C0 * M[4]) + (C1 * M[5]));
       sol[idx + 3905] = ((C0 * M[5]) + (C1 * M[6]));
       sol[idx + 3906] = ((C0 * M[6]) + (C1 * M[7]));
       sol[idx + 3907] = ((C0 * M[7]) + (C1 * M[8]));
       sol[idx + 1944] = ((C0 * M[9]) + (C1 * M[10]));
       sol[idx + 1945] = ((C0 * M[10]) + (C1 * M[11]));
       sol[idx + 1946] = ((C0 * M[11]) + (C1 * M[12]));
       sol[idx + 1947] = ((C0 * M[12]) + (C1 * M[13]));
       sol[idx + 1948] = ((C0 * M[13]) + (C1 * M[14]));
       sol[idx + 1949] = ((C0 * M[14]) + (C1 * M[15]));
       sol[idx + 32] = ((C0 * M[16]) + (C1 * M[17]));
       sol[idx + 33] = ((C0 * M[17]) + (C1 * M[18]));
       sol[idx + 34] = ((C0 * M[18]) + (C1 * M[19]));
       sol[idx + 35] = ((C0 * M[19]) + (C1 * M[20]));
       sol[idx + 36] = ((C0 * M[20]) + (C1 * M[21]));
       sol[idx + 37] = ((C0 * M[21]) + (C1 * M[22]));
       sol[idx + 38] = ((C0 * M[22]) + (C1 * M[23]));
       sol[idx + 17] = ((C0 * M[24]) + (C1 * M[25]));
       sol[idx + 18] = ((C0 * M[25]) + (C1 * M[26]));
       sol[idx + 19] = ((C0 * M[26]) + (C1 * M[27]));
       sol[idx + 20] = ((C0 * M[27]) + (C1 * M[28]));
       sol[idx + 21] = ((C0 * M[28]) + (C1 * M[29]));
       sol[idx + 22] = ((C0 * M[29]) + (C1 * M[30]));
       sol[idx + 23] = ((C0 * M[30]) + (C1 * M[31]));
     }
  }
}