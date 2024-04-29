Code: #pragma ACCEL kernel

void kernel_ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  ellpack(nzval,cols,vec,out);
}