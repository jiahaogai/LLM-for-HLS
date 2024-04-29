<<<<<<< HEAD
#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{2}
double ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  double nzval_tmp;
  int cols_tmp;
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
  for (j = 0; j < 494; j++) {
    sum = ((double )0);
    double nzval_tmp_0 = nzval[0];
    int cols_tmp_0 = cols[0];
//#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 0; i < 490; i++) {
      nzval_tmp = nzval_tmp_0;
      cols_tmp = cols_tmp_0;
      sum += nzval_tmp * vec[cols_tmp];
      nzval_tmp_0 = nzval[i + 1];
      cols_tmp_0 = cols[i + 1];
    }
    out[j] = sum;
=======
#pragma End of Directives: 
#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 494; i++) {
    out[i] = ((double )0);
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = cols[i]; j < cols[i + 1]; j++) {
      out[i] += nzval[j] * vec[cols[j]];
    }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}