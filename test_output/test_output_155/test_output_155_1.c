

5.  Don't automatically distribute this loop on nodes or cores.
```c
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for(j = 1; j < 31; j++) {
      y_0 = _in_0[0] + _in_2[0];
      y_1 = _in_0[1] + _in_2[1];
  
      z_0 = _in_0[0] - _in_2[0];
      z_1 = _in_0[1] - _in_2[1];
  
      _out_0[0] = y_0 + (sqrt(2.0) * z_1);
      _out_0[1] = y_1 + (sqrt(2.0) * z_0);
      _out_2[0] = y_0 - (sqrt(2.0) * z_1);
      _out_2[1] = y_1 - (sqrt(2.0) * z_0);
  
      for(i = 1; i < 31; i++) {
          y_0 = _in_0[2 * i] + _in_2[2 * i];
          y_1 = _in_0[2 * i + 1] + _in_2[2 * i + 1];
  
          z_0 = _in_0[2 * i] - _in_2[2 * i];
          z_1 = _in_0[2 * i + 1] - _in_2[2 * i + 1];
  
          _out_1[2 * i] = y_0 + (sqrt(2.0) * z_1);
          _out_1[2 * i + 1] = y_1 + (sqrt(2.0) * z_0);
          _out_3[2 * i] = y_0 - (sqrt(2.0) * z_1);
          _out_3[2 * i + 1] = y_1 - (sqrt(2.0) * z_0);
      }
      _in_0 = _out_0;
      _in_2 = _out_2;
      _out_0 = _out_1;
      _out_2 = _out_3;
  }
}
```
