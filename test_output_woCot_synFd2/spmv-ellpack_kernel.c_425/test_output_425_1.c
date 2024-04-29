The resulting C code is:

c
 #pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double Si;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{19}
  for (i = 0; i < 494; i++) {
    double sum = ((double )0);
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 10; j++) {
      Si = nzval[j + i * 10] * vec[cols[j + i * 10]];
      sum += Si;
    }
    out[i] = sum;
  }
}