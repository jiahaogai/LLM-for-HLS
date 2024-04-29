<<<<<<< HEAD
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
=======
#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
{
  int i;
  int j;
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
  
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (j = 0; j < 4940; j++) {
    out[cols[j]] += nzval[j] * vec[i];
=======
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{19}
  for (j = 0; j < 16; j++) {
    
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{1}
    for (i = 0; i < 48; i++) {
      out[cols[j * 48 + i]] += nzval[j * 48 + i] * vec[j];
    }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}