#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{19}

double nzval[4940]/* total size: 4940 */;
int cols[4940]/* total size: 4940 */;
double vec[494]/* total size: 494 */;
double out[494]/* total size: 494 */;
  
#pragma ACCEL kernel
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
void kernel_ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (j = 0; j < 4940; j++) {
    out[cols[j]] += nzval[j] * vec[i];
  }
}