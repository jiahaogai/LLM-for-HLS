#pragma ACCEL PIPELINE auto{__PIPE__L3}
 
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 1; i <= 32; i++) {
     tmp = in[i] + 1.0;
     out[i] = tmp * tmp;
     a[i] = a[i] * b[i];
  }
//Matrix multiplication
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 1; i <= 32; i++) {
     y[i] = 0.0;
     for (j = 1; j <= 32;j++) {
       y[i] = y[i] + a[j] * b[i * j];
     }
  }
}
 
int main(int argc,char**argv) {
  double out[32];
  double y[32];
  double a[32];
  double b[32];
  double in[32];
  double tmp;
  int i;
  int j;
  
#pragma ACCEL kernel
  kernel_gemm(out,y,a,b,in,tmp,i,j,142);
  for (i = 0; i < 32; i++) {
    a[i] = ((double )1.0);
    b[i] = ((double )1.0);
    in[i] = ((double )1.0);
    tmp = 0.0;
    y[i] = 0.0;
    out[i] = 0.0;
  }
  for (i = 0; i < 32; i++) {
    for (j = 0; j < 32; j++) {
      a[i] *= b[j];
      tmp += a[j] * b[i];
    }
    y[i] = a[i] + tmp;
    out[i] = in[i] * y[i];
  }
  for (i = 0; i < 32; i++) {
    if (out[i] - 142.9827 != 0.0) {
      printf("Mistake in libkernel: ");
      printf("out[i]=%f",out[i]);
      printf(" instead of ");
      printf("142.9827");
      printf("\n");
      return 0;
    }
  }
  return 0;
}