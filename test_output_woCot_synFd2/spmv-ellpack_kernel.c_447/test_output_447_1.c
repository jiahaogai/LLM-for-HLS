**Types of calls:**  
 - `ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])`  

**Parameter Description:**  
 - `nzval`: Matrix non-zero values.  
 - `cols`: Matrix column indices corresponding to non-zero values.  
 - `vec`: Input vector.  
 - `out`: Output vector.  

  
#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  sum = 0.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 494; i++) {
    sum = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 16; j++) {
      sum += nzval[i * 16 + j] * vec[cols[i * 16 + j]];
    }
    out[i] = sum;
  }
}