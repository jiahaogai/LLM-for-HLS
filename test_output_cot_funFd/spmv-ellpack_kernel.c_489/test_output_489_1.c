Code: #pragma ACCEL kernel
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{4}

#pragma ACCEL PARALLEL FACTOR=auto{4}
void kernel_csr(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 494; i++) {
    out[i] = ((double )0);
    
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{16}
    for (j = 0; j < 10; j++) {
      out[i] += nzval[cols[10 * i + j]] * vec[cols[10 * i + j]];
    }
  }
}
#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  kernel_ellpack(nzval,cols,vec,out);
}
#pragma ACCEL kernel

void csr(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  kernel_csr(nzval,cols,vec,out);
}