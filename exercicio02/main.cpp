// System Headers
#include <cmath>
#include <cstdint>
#include <iostream>

// OpenCv Headers
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

// MatPlot++ Headers
#include <matplot/matplot.h>

using namespace std;
using namespace cv;
using namespace matplot;

vector<double> createDataVectorFromLayer(Mat bgrMat, uint8_t layer);
void plotHistogram(vector<double> dataVector, const string windowName,
                   uint16_t subplotIndex);
vector<double> createHistogramFromDataVector(vector<double> dataVector);
vector<double> createCumulativeHistogramFromHistogram(vector<double> histogram);

int main(int argc, char *argv[]) {

  Mat image;
  image = imread(argv[1], IMREAD_COLOR);

  vector<double> histogram = createDataVectorFromLayer(image, 0);
  plotHistogram(histogram, "Histogram - Blue Layer", 0);
  histogram = createDataVectorFromLayer(image, 1);
  plotHistogram(histogram, "Histogram - Green Layer", 1);
  histogram = createDataVectorFromLayer(image, 2);
  plotHistogram(histogram, "Histogram - Red Layer", 2);
  vector<double> cummulativeHistogram =
      createCumulativeHistogramFromHistogram(histogram);
  plotHistogram(cummulativeHistogram, "Cummulative Histogram - Red Layer", 3);
  show();

  return 0;
}

vector<double> createDataVectorFromLayer(Mat bgrMat, uint8_t layer) {
  vector<double> hist;

  for (uint16_t i = 0; i < bgrMat.rows; i++) {
    for (uint16_t j = 0; j < bgrMat.cols; j++) {
      Vec3b current_BGR_pixel = bgrMat.at<Vec3b>(i, j);
      hist.push_back(current_BGR_pixel[layer]);
    }
  }
  return hist;
}

void plotHistogram(vector<double> dataVector, const string windowName,
                   uint16_t subplotIndex) {
  subplot(3, 3, subplotIndex);
  auto h = hist(dataVector);
  title(windowName);
}

vector<double> createHistogramFromDataVector(vector<double> dataVector) {
  vector<double> hist(256, 0);
  for (uint16_t i = 0; i < hist.size(); i++) {
    hist[dataVector[i]]++;
  }
  return hist;
}

vector<double> createNormalizedHistogramFromHistogram(vector<double> histogram,
                                                      Mat bgrMat) {
  vector<double> normalizedHist(256, 0);
  uint64_t number_of_pixels = bgrMat.rows * bgrMat.cols;
  for (uint16_t i = 0; i < histogram.size(); i++) {
    normalizedHist[i] = (double)histogram[i] / (double)number_of_pixels;
  }
  return normalizedHist;
}

vector<double>
createCumulativeHistogramFromHistogram(vector<double> histogram) {
  vector<double> cummulativeHistogram(256, 0);
  cummulativeHistogram[0] = histogram[0];
  for (uint16_t i = 1; i < histogram.size(); i++) {
    cummulativeHistogram[i] = cummulativeHistogram[i - 1] + histogram[i];
    cout << cummulativeHistogram[i] << endl;
  }
  return cummulativeHistogram;
}
