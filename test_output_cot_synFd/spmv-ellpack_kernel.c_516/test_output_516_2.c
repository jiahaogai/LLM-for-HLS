Code: #pragma ACCEL kernel

void kernel_ellpack_15(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  spmv_1:
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    spmv_2:
    for (j = 0; j < 49; j++) {
      sum += nzval[(i * 49) + j] * vec[cols[(i * 49) + j]];
    }
    out[i] = sum;
  }
}
#pragma ACCEL kernel

void kernel_ellpack_16(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  spmv_1:
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    spmv_2:
    for (j = 0; j < 49; j++) {
      sum += nzval[(i * 49) + j] * vec[cols[(i * 49) + j]];
    }
    out[i] = sum;
  }
}
#pragma ACCEL kernel

void kernel_ellpack_17(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  spmv_1:
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    spmv_2:
    for (j = 0; j < 49; j++) {
      sum += nzval[(i * 49) + j] * vec[cols[(i * 49) + j]];
    }
    out[i] = sum;
  }
}
#pragma ACCEL kernel

void kernel_ellpack_18(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  spmv_1:
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    spmv_2:
    for (j = 0; j < 49; j++) {
      sum += nzval[(i * 49) + j] * vec[cols[(i * 49) + j]];
    }
    out[i] = sum;
  }
}
#pragma ACCEL kernel

void kernel_ellpack_19(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR