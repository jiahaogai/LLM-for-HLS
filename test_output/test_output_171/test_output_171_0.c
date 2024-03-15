
auto tmax = 40;
auto n = 40;
 
#pragma ACCEL kernel

void gemm(double m1[40][40],double m2[40][40],double prod[40][40])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 40; j++) {
      double sum = (double )0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      for (k = 0; k < 40; k++) {
        sum += m1[i][k] * m2[k][j];
      }
      prod[i][j] = sum;
    }
  }
//#pragma endscop
}
