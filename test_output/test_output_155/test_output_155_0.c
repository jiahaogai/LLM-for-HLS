

5.  Don't automatically distribute this loop.
```c
#pragma ACCEL DISTRIBUTE FACTOR=1
  for (tfix=0;tfix<20;tfix++) {
    a[0] = ((long )0);
    b[0] =  ((long )1);
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (i=1; i<120; i++) {
      a[i] =  a[i-1] +  b[i-1];
      b[i] =  a[i] +  b[i];
    }
  }
```

