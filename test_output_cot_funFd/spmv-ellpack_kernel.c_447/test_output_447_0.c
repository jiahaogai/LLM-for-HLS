**Optimized for:**  
`[AutoFPO]`

**Standardization:**  
`[None]`

**Additional Notes:**  
`  
  Products:
  nzval[i] * cols[j]^vec[j] for i in 0..4939, j in 0..4
`  

 
  
#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (j = 0; j < 4940; j++) {
    out[cols[j]] += nzval[j] * vec[j];
  }
}