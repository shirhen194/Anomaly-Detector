#include "timeseries.h"
#include <string.h>

int TimeSeries::getNumberOfColumns() const {return 1;}
float* TimeSeries::getVectorFeature(int i) const{}
int TimeSeries::getNumberOfRows() const {}
string TimeSeries::getFeatureName(int i) const{}