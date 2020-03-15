#pragma once

// Precision used for determining whether two doubles are equal
const double D_PREC(1e-10);

// Returns whether two doubles are equal +- D_PREC
bool isEqual(double, double);
