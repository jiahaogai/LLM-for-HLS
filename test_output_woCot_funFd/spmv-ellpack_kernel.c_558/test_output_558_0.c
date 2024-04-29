**Parameters**:

  - `nzval`: An array of nonzero values in a sparse matrix.
  - `cols`: An array of column indices for entries in a sparse matrix.
  - `vec`: A vector to multiply by the sparse matrix.
  - `out`: The result of the sparse matrix-vector multiplication.

**Example**:


 #pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  double val;
  double v;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  spmv_1:
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    spmv_2:
    for (j = cols[i]; j < cols[i + 1]; j++) {
      val = nzval[j];
      v = vec[cols[j]];
      sum += val * v;
    }
    out[i] = sum;
  }
}