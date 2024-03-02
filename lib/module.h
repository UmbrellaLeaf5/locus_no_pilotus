#pragma once

// Get water vapor density on specified height.
// SRC: (2.25) from citation
//   rho_w : water vapor density, g/m**3
//   h : height above sea level, m
//   rh : relative humidity, n/d
//   pho_w_max : saturated vapor density, g/m**3
double rho_w(double h, double rh = 0.6, double pho_w_max = 12.8 * 0.001);
