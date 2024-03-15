

"Automatically determine the parallelization factor for the inner loop, allowing up to 4 parallel instances"
#pragma ACCEL PARALLEL FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (t = 0; t < 40; t++) {
    float dt = (t * 0.01);
    float sin_dt = sin(dt);
    float cos_dt = cos(dt);
    float temp1 = u[0] - sin_dt * (u[1] + u[2]);
    float temp2 = u[1] + u[2] * cos_dt - 0.5 * (u[0] - sin_dt * (u[1] + u[2]));
    float temp3 = u[2] * cos_dt + u[1] * (-sin_dt) - 0.5 * (u[0] - sin_dt * (u[1] + u[2]));
    f[0] = temp1 * (u[0] * u[0] + u[1] * u[1] + u[2] * u[2]) + 2.0 * (u[1] * u[1] + u[2] * u[2]) + (u[1] * u[1] + u[2] * u[2]);
    f[1] = temp1 * u[1] + temp2 * (u[0] * u[0] + u[1] * u[1] + u[2] * u[2]) + 2.0 * (u[1] * u[2]) ;
    f[2] = temp1 * u[2] + temp3 * (u[0] * u[0] + u[1] * u[1] + u[2] * u[2]) + 2.0 * (u[1] * u[2]) ;
    u[0] = temp1;
    u[1] = temp2;
    u[2] = temp3;
  }
}
