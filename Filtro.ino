float filtro() {
  mike.setFrequency(80000);
  mike.begin();
  float i1 = 0;
  float x[5] = { 0, 0, 0, 0, 0 };
  float y[5] = { 0, 0, 0, 0, 0 };
  float e[5] = { 0.04658291, 0.18633163, 0.27949744, 0.18633163, 0.04658291 };
  float g[5] = { 1., 0.7820952, -0.67997853, 0.1826757, -0.03011888 };
  for (int i = 0; i < 200; i++) {
    x[0] = mike.read();
    y[0] = e[0] * x[0] + e[1] * x[1] + e[2] * x[2] + e[3] * x[3] + e[4] * x[4]
           + g[1] * y[1] + g[2] * y[2] + g[3] * y[3] + g[4] * y[4];
    x[4] = x[3];
    y[4] = y[3];
    x[3] = x[2];
    y[3] = y[2];
    x[2] = x[1];
    y[2] = y[1];
    x[1] = x[0];
    y[1] = y[0];
  }
  mike.end();
  return y[0];
}