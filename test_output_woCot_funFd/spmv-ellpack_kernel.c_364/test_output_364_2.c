<<<<<<< HEAD
Code: #pragma ACCEL kernel

=======
#pragma ACCEL PIPELINE auto{flatten}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{16}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
<<<<<<< HEAD
  double sum;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
    for (j = 0; j < 4; j++) {
      sum += nzval[i * 4 + j] * vec[cols[i * 4 + j]];
    }
    out[i] = sum;
  }
//#pragma endscop
=======
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (j = 0; j < 64; j++) {
    double temp_1;
    int k;
    double sum;
    sum = 0.0;
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
    for (k = 0; k < 64; k++) {
      double nzval_tmp;
      int cols_tmp;
      nzval_tmp = nzval[((j * 64) + k)];
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      cols_tmp = cols[((j * 64) + k)];
      sum += nzval_tmp * vec[cols_tmp];
    }
    temp_1 = sum + out[j];
    out[j] = temp_1;
  }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}