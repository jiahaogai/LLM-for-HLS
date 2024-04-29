**Basic Parameters:**

| |C|A|B|
|---|---|---|---|
|**Range**|${80:80}$|${0:60}$|${0:60}$|
|**Row**|${0:80}$|${0:80}$|${0:80}$|
|**Element**|${0:1}$|${0:1}$|${0:1}$|
|**Arithmetic Type**|${double}$|${double}$|${double}$|

**Dereferencing Operators:**

| |C|A|B|
|---|---|---|---|
|**Range**|.|[ ]|[ ]|
|**Row**|.|.|.|
|**Element**|[ ]|[ ]|[ ]|

**Arithmetic Operations:**

| |C|A|B|alpha|beta|x|y|
|---|---|---|---|---|---|---|---|
|**Arith.**|Assign|Multiply|Multiply|Multiply|Multiply|Add|Assign|
|**Assign**|C[i][j]|A[i][k]|B[i][k]|tmp_0|tmp_1|sum|A[i][j]|
|**Multiply**| — |A[i][k]|B[i][k]|tmp_0| — | — |
|**Multiply**| — |B[i][k]|A[i][k]|tmp_1| — | — |
|**Multiply**| — |A[i][k]|B[i][k]|tmp_0| — | — |
|**Multiply**| — |B[i][k]|A[i][k]|tmp_1| — | — |
|**Add**| — | — | — |alpha * tmp_0|beta * tmp_1|sum|C[i][j]|

---

#pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
{
  int i;
  int j;
  int k;
  double tmp_0;
  double tmp_1;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 80; j++) {
      sum = 0.0;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (k = 0; k < 60; k++) {
        tmp_0 = A[i][k] * B[k][j];
        tmp_1 = B[i][k] * A[k][j];
        sum += alpha * tmp_0 + tmp_1;
      }
      C[i][j] += beta * sum;
    }
  }
}