5. `#pragma ACCEL PARAM nzval[]`: Declares the `nzval` parameter as a memory array.

6. `#pragma ACCEL PARAM cols[]`: Declares the `cols` parameter as a memory array.

7. `#pragma ACCEL PARAM vec[]`: Declares the `vec` parameter as a memory array.

8. `#pragma ACCEL PARAM out[]`: Declares the `out` parameter as a memory array.

#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  double val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  spmv_1:
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    spmv_2:
    for (j = 0; j < 32; j++) {
      val = nzval[i * 32 + j];
      sum += val * vec[cols[i * 32 + j]];
    }
    out[i] = sum;
  }
}