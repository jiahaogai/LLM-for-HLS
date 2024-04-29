#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
int main(int argc, char **argv)
{
  double nzval[4940] ;
  int cols[4940] ;
  double vec[494] ;
  double out[494] ;
  int i ;
  int j ;
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 440; i++) {
    double sum = ((double )0);
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
    for (j = 0; j < 20; j++) {
      int n = i * 20 + j;
      sum += nzval[n] * vec[cols[n]];
    }
    out[i] = sum;
  }
//#pragma ACCEL PIPELINE auto{off}
//#pragma ACCEL TILE FACTOR=auto{1}
//#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 494; i++) {
    printf("%lf\n", out[i]);
  }
  return 0;
}