4. **Optimize**
   
#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (j = 0; j < 4; j++) {
    
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{8}
    for (i = 0; i < 121; i++) {
      out[cols[i + j * 121]] += nzval[i + j * 121] * vec[j];
    }
  }
}