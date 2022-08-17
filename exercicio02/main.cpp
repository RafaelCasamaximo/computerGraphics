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

vector<double> createHistogramFromLayer(Mat bgrMat, uint16_t layerIndex);
vector<double> createNormalizedHistogram(vector<double> histogram,
                                         uint64_t totalOfPixels);
vector<double> createCummulativeHistogram(vector<double> histogram);
Mat equalizeHistogram(Mat bgrMat, vector<vector<double>> bgrCumHist);

int main(int argc, char *argv[]) {

  if (argc < 3) {
    cout << "USAGE ./main [PATH] [0: Show Histograms/ 1: Show Images]" << endl;
    exit(-1);
  }

  Mat image;
  image = imread(argv[1], IMREAD_COLOR);

  // Calculo de histograma das camadas bgr da imagem
  vector<double> bHist = createHistogramFromLayer(image, 0);
  vector<double> gHist = createHistogramFromLayer(image, 1);
  vector<double> rHist = createHistogramFromLayer(image, 2);
  vector<vector<double>> bgrHist{bHist, gHist, rHist};

  // Calculo do histograma normalizado
  uint64_t totalOfPixels = image.rows * image.cols;
  vector<double> bNormHist = createNormalizedHistogram(bHist, totalOfPixels);
  vector<double> gNormHist = createNormalizedHistogram(gHist, totalOfPixels);
  vector<double> rNormHist = createNormalizedHistogram(rHist, totalOfPixels);
  vector<vector<double>> bgrNormHist{bNormHist, gNormHist, rNormHist};

  // Calculo do histograma cumulativo normalizado
  vector<double> bNormCumHist = createCummulativeHistogram(bNormHist);
  vector<double> gNormCumHist = createCummulativeHistogram(gNormHist);
  vector<double> rNormCumHist = createCummulativeHistogram(rNormHist);
  vector<vector<double>> bgrNormCumHist{bNormCumHist, gNormCumHist,
                                        rNormCumHist};

  // Calculo da equalização do histograma cumulativo normalizado junto da imagem
  Mat equalizedImage;
  equalizedImage = equalizeHistogram(image, bgrNormCumHist);

  // Calculo de histograma das camadas bgr da imagem
  vector<double> bEHist = createHistogramFromLayer(equalizedImage, 0);
  vector<double> gEHist = createHistogramFromLayer(equalizedImage, 1);
  vector<double> rEHist = createHistogramFromLayer(equalizedImage, 2);
  vector<vector<double>> bgrEHist{bEHist, gEHist, rEHist};

  switch (atoi(argv[2])) {
  case 0: {
    // Plot dos histogramas
    subplot(4, 1, 0);
    barstacked(bgrHist);
    subplot(4, 1, 1);
    barstacked(bgrNormHist);
    subplot(4, 1, 2);
    barstacked(bgrNormCumHist);
    subplot(4, 1, 3);
    barstacked(bgrEHist);
    show();
    break;
  }
  case 1: {
    // Plot da imagem
    cv::imshow("Original Image", image);
    cv::imshow("Equalized Image", equalizedImage);
    waitKey(0);
    break;
  }
  default: {
    cout << "USAGE ./main [PATH] [0: Show Histograms/ 1: Show Images]" << endl;
    exit(-1);
  }
  }
  return 0;
}

vector<double> createHistogramFromLayer(Mat bgrMat, uint16_t layerIndex) {
  vector<double> histogram(256, 0);

  for (uint16_t i = 0; i < bgrMat.rows; i++) {
    for (uint16_t j = 0; j < bgrMat.cols; j++) {
      Vec3b bgrPixel = bgrMat.at<Vec3b>(i, j);
      histogram[bgrPixel[layerIndex]]++;
    }
  }
  return histogram;
}

vector<double> createNormalizedHistogram(vector<double> histogram,
                                         uint64_t totalOfPixels) {
  vector<double> normalizedHistogram(256);

  for (uint16_t i = 0; i < histogram.size(); i++) {
    normalizedHistogram[i] = (double)histogram[i] / (double)totalOfPixels;
  }
  return normalizedHistogram;
}

vector<double> createCummulativeHistogram(vector<double> histogram) {
  vector<double> cummmulativeHistogram(256, 0);
  cummmulativeHistogram[0] = histogram[0];
  for (uint16_t i = 1; i < histogram.size(); i++) {
    cummmulativeHistogram[i] = cummmulativeHistogram[i - 1] + histogram[i];
  }
  return cummmulativeHistogram;
}

Mat equalizeHistogram(Mat bgrMat, vector<vector<double>> bgrCumHist) {
  Mat eqMat(bgrMat.size(), CV_8UC3);
  for (uint64_t i = 0; i < bgrMat.rows; i++) {
    for (uint64_t j = 0; j < bgrMat.cols; j++) {
      for (uint16_t k = 0; k < 3; k++) {
        eqMat.at<Vec3b>(i, j)[k] =
            255 * bgrCumHist[k][bgrMat.at<Vec3b>(i, j)[k]];
      }
    }
  }
  return eqMat;
}
