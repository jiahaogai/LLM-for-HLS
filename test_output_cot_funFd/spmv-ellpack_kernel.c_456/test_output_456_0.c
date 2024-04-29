#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  double v;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    v = ((double )0);
    
#pragma ACCEL PARAMS FACTOR=auto{2}
    for (j = 0; j < 5; j++) {
      v = nzval[i * 5 + j];
      
#pragma ACCEL PARAMS FACTOR=auto{1}
      sum = sum + v * vec[cols[i * 5 + j]];
    }
    out[i] = sum;
  }
}