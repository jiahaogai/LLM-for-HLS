Code: #pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  kernel_ellpack(nzval,cols,vec,out);
}