#pragma ACCEL kernel

void kernel_doitgen(int tsteps,int n,double A[120][120],double C4[120][120],double sum[120])
{
  int t;
  int i;
  int j;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{4}
  for (t = 0; t <= 39; t++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (i = 0; i <= 118; i++) {
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{__PARA__L2}
      for (j = 0; j <= 118; j++) {
        if (i == j) {
          sum[i] = 0.0;
        }
        else {
          double _tmp_tmp = A[i][j];
          sum[i] += _tmp_tmp * C4[j][t];
        }
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    for (i = 0; i <= 118; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      for (j = 0; j <= 118; j++) {
        double _tmp_sum = sum[j];
        A[i][j] = A[i][j] + _tmp_sum;
      }
    }
  }
//#pragma endscop
}