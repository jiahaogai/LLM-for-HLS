5. `#pragma ACCEL PARAM nzval[]`: Specifies that the argument `nzval` is a memory array.

6. `#pragma ACCEL PARAM cols[]`: Specifies that the argument `cols` is a memory array.

7. `#pragma ACCEL PARAM vec[]`: Specifies that the argument `vec` is a memory array.

8. `#pragma ACCEL PARAM out[]`: Specifies that the argument `out` is a memory array.

#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  spmv_1:
  for (i = 0; i < 494; i++) {
    out[i] = ((double )0);
    spmv_2:
    for (j = 0; j < 32; j++) {
      out[i] += nzval[i * 32 + j] * vec[cols[i * 32 + j]];
    }
  }
}