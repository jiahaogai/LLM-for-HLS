Code: #pragma ACCEL kernel

void kernel_gemm(char transa,char transb,int m,int n,int k,double alpha,double a[400][400],double b[400][400],double beta,double c[400][400])
{
  int r;
  int q;
  int p;
  int j;
  int i;
  int jj;
  int pp;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      c[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (p = 0; p < 400; p += 16) {
      
#pragma ACCEL PARALLEL reduction=c FACTOR=auto{10}
      for (jj = 0; jj < 400; jj += 16) {
        pp = p;
        double sum = (double )0;
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
	for (j = jj; j < jj + 16 && j < 400; j++) {
          mult = alpha * a[pp][j];
          sum += mult * b[j][jj];
        }
	c[pp][jj] += sum;
      }
    }
  }
}