
 #pragma ACCEL kernel

void kernel_correlation(double float_n,double data[100][80],double corr[80][80],double tmp[80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (j = 0; j < 80; j++) {
    tmp[j] = 0.0;
    
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{__PARA__L2}
    for (i = 0; i < 100; i++) {
      tmp[j] += data[i][j] / float_n;
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  for (i = 0; i < 100; i++) {
    
#pragma ACCEL PARALLEL reduction=corr FACTOR=auto{__PARA__L3}
    for (j = 0; j < 80; j++) {
      corr[i][j] = tmp[j] - data[i][j] / float_n;
    }
  }
//#pragma endscop
}
