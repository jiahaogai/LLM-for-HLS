#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
double nzval[4940];
int cols[4940];
double vec[494];
double out[494];
void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 0; i < 494; i++) {
    out[i] = ((double )0);
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 16; j++) {
      out[i] += nzval[cols[i + j * 494] - 1] * vec[cols[i + j * 494] - 1];
    }
  }
}