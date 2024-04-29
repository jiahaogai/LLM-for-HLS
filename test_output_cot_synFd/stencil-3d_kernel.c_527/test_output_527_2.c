#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{1}
void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long NX;
  long NY;
  long NZ;
  long P;
  long Q;
  long R;
  long M;
  long pad_size;
  long field_size;
  long idxm;
  long idxn;
  long idxk;
  long idxP;
  long idxQ;
  long idxR;
  long diff;
  long a;
//#pragma scop
  NX = 32;
  NY = 32;
  NZ = 32;
  P = 1;
  Q = 1;
  R = 1;
  M = NX - 2 * P;
  pad_size = NX * NY * NZ * sizeof(long) / 4;
// Field size is the size of the original array, less the padding
  field_size = ((NX - 2 * P) * (NY - 2 * Q) * (NZ - 2 * R) - 1) * sizeof(long);
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 39304; i++) {
    orig[i] = ((long )0);
  }
// Pad the field with 'pad_size' bytes of zeros
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < pad_size; i++) {
    sol[i] = ((long )0);
  }
// Compute the stencil
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = P; i < NX - P; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = Q; j < NY - Q; j++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = R; k < NZ - R; k++) {
        idx = i * (NY - 2 * Q) * (NZ - 2 * R) + j * (NZ - 2 * R) + k;
        idxm = (i - 1) * (NY - 2 * Q) * (NZ - 2 * R) + j * (NZ - 2 * R) + k;
        idxn = i * (NY - 2 * Q) * (NZ - 2 * R) + (j - 1) * (NZ - 2 * R) + k;
        idxk = i * (NY - 2 * Q) * (NZ - 2 * R) + j * (NZ - 2 * R) + (k - 1);
        idxP = (i - 1) * (NY - 2 * Q) * (NZ - 2 * R) + j * (NZ - 2 * R) + k;
        idxQ = i * (NY - 2 * Q) * (NZ - 2 * R) + (j - 1) * (NZ - 2 * R) + k;
        idxR = i * (NY - 2 * Q) * (NZ - 2 * R) + j * (NZ - 2 * R) + (k - 1);
        a = orig[idxm + 1] + orig[idxn + NZ] + orig[idxk + 1 * NY * NZ] - orig[idxm + 1 + NZ] - orig[idxn + 1] - orig[idxk] + orig[idxP + 1 + NZ] + orig[idxQ + NZ] + orig[idxR + 1];
        sol[idx] = a;
      }
    }
  }
//#pragma endscop
}