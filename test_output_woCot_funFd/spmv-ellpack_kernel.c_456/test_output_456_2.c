<<<<<<< HEAD
Code: #pragma ACCEL kernel
=======
Code: #pragma ACCEL PIPELINE auto{off}`:
   Do not automatically pipeline this loop.

2. `#pragma ACCEL TILE FACTOR=auto{8}`:
   Divide this loop into smaller parts with a factor of 8 to improve parallelism.

3. `#pragma ACCEL PARALLEL FACTOR=auto{2}`:
   Execute loop iterations concurrently with a factor of 2 to make use of parallelism.

4. `#pragma ACCEL kernel`:
   Designate the following function for hardware acceleration.
Code: #pragma ACCEL PARAMS auto{nzval}={4940} auto{cols}={4940} auto{vec}={494} auto{out}={494}`:
   Populate the kernel's arguments.

6. `#pragma ACCEL PARAMS auto{off}`:
   Turn off array reduction for argument `nzval`.

7. `#pragma ACCEL PARAMS auto{off}`:
   Turn off array reduction for argument `cols`.

8. `#pragma ACCEL PARAMS auto{vec}`:
   Enable array reduction for argument `vec`.

9. `#pragma ACCEL PARAMS auto{out}`:
   Enable array reduction for argument `out`.

#pragma ACCEL kernel
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
<<<<<<< HEAD
  for (i = 0; i < 494; i++) {
    out[i] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 16; j++) {
      out[i] += nzval[cols[i * 16 + j]] * vec[j];
    }
  }
}
=======
  spmv_1:
  for (i = 0; i < 494; i++) {
    out[i] = ((double )0);
    spmv_2:
    for (j = cols[i]; j < cols[i + 1]; j++) {
      out[i] += nzval[j] * vec[cols[j]];
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}`:
   Do not automatically pipeline this loop.

2. `#pragma ACCEL TILE FACTOR=auto{8}`:
   Divide this loop into smaller parts with a factor of 8 to improve parallelism.

3. `#pragma ACCEL PARALLEL FACTOR=auto{2}`:
   Execute loop iterations concurrently with a factor of 2 to make use of parallelism.

4. `#pragma ACCEL kernel`:
   Designate the following function for hardware acceleration.
Code: #pragma ACCEL PARAMS auto{nzval}={4940} auto{cols}={4940} auto{vec}={494} auto{out}={494}`:
   Populate the kernel's arguments.

6. `#pragma ACCEL PARAMS auto{off}`:
   Turn off array reduction for argument `nzval`.

7. `#pragma ACCEL PARAMS auto{off}`:
   Turn off array reduction for argument `cols`.

8. `#pragma ACCEL PARAMS auto{vec}`:
   Enable array reduction for argument `vec`.

9. `#pragma ACCEL PARAMS auto{out}`:
   Enable array reduction for argument `out`.

#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 494; i++) {
    out[i] = ((double )0);
    
#pragma ACCEL PARAMS FACTOR=auto{16}
    for (j = 0
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
