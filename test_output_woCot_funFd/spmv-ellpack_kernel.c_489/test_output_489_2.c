<<<<<<< HEAD
#pragma ACCEL PIPELINE auto{off}
=======
Code: #pragma ACCEL PIPELINE auto{off}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a

#pragma ACCEL TILE FACTOR=auto{4}

#pragma ACCEL PARALLEL FACTOR=auto{4}
void kernel_ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{1}
=======
#pragma ACCEL PARALLEL FACTOR=auto{16}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  for (i = 0; i < 494; i++) {
    out[i] = ((double )0);
    
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{16}
    for (j = 0; j < 16; j++) {
<<<<<<< HEAD
      out[i] += nzval[i * 16 + j] * vec[cols[i * 16 + j]];
    }
  }
}
=======
      out[i] += nzval[(i * 16) + j] * vec[cols[(i * 16) + j]];
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{4}

#pragma ACCEL PARALLEL FACTOR=auto{4}
void kernel_ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 494; i++) {
    out[i] = ((double )0);
    
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{16}
    for (j = 0; j < 16; j++) {
      out[i] += nzval[(i * 16) + j] * vec[cols[(i * 16) + j]];
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{4}

#pragma ACCEL PARALLEL FACTOR=auto{4}
void kernel_ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 494; i++) {
    out[i] = ((double )0);
    
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{16}
    for (j = 0; j < 16; j++) {
      out[i] += nzval[(i * 16) + j] * vec[cols[(i * 16) + j]];
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{4}

#pragma ACCEL PARALLEL FACTOR=auto{4}
void kernel_ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 494; i++) {
    out[i] = ((double )0);
    
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{16}
    for (j = 0; j < 16; j++) {
      out[i] += nzval[(i * 16) + j] * vec[cols[(i * 16) + j]];
    }
  }
}
Error: 
Please check the code and try again.
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
