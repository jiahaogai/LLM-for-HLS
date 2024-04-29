#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{19}
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    int ell_begin = cols[i];
    int ell_end = cols[i + 1];
    int ell_size = ell_end - ell_begin;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < ell_size; j++) {
      sum += nzval[j + ell_begin] * vec[j + ell_begin];
    }
    out[i] = sum;
  }
}