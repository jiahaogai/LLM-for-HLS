#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{13}
  for (j = 0; j < 16; j++) {
    i = 0 + 16 * j;
    
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{13}
    while (i < 494 && cols[i] == j) {
      out[i] += nzval[i] * vec[j];
      i++;
    }
  }
}