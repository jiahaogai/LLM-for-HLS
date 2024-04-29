#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (j = 0; j < 10; j++) {
    int idx = 0;
    while (idx < 4940 && cols[idx] != j) {
      idx++;
    }
    if (idx < 4940) {
      out[i] += nzval[idx] * vec[j];
    }
  }
}