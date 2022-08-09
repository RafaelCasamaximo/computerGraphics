#include <algorithm>
#include <cmath>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

enum BGR { BLUE, GREEN, RED };

Mat BGR_to_CMY(Mat bgrMat);
Mat BGR_to_CMYK(Mat bgrMat);
Mat BGR_to_HSI(Mat bgrMat);

int main(int argc, char *argv[]) {

  if (argc < 3) {
    cout << "USAGE: ./main [PATH] [0: CMY/ 1: CMKY/ 2: HSI]" << endl;
    exit(-1);
  }

  Mat imagem;
  imagem = imread(argv[1], IMREAD_COLOR);

  imshow("ORIGINAL", imagem);

  switch (atoi(argv[2])) {
  case 0: {
    Mat cmyImagem = BGR_to_CMY(imagem);
    Mat channel[3];
    split(cmyImagem, channel);

    imshow("CMY - CYAN", channel[0]);
    imshow("CMY - MAGENTA", channel[1]);
    imshow("CMY - YELLOW", channel[2]);

    waitKey(0);

    break;
  }
  case 1: {
    Mat cmykImagem = BGR_to_CMYK(imagem);
    Mat channel[4];
    split(cmykImagem, channel);

    imshow("CMYK - CYAN", channel[0]);
    imshow("CMYK - MAGENTA", channel[1]);
    imshow("CMYK - YELLOW", channel[2]);
    imshow("CMYK - KEY", channel[3]);

    waitKey(0);

    break;
  }
  case 2: {
    Mat hsiImagem = BGR_to_HSI(imagem);
    Mat channel[3];
    split(hsiImagem, channel);

    imshow("HSI - HUE", channel[0]);
    imshow("HSI - SATURATION", channel[1]);
    imshow("HSI - INTENSITY", channel[2]);

    waitKey(0);
    break;
  }
  default: {
    cout << "USAGE: ./main [PATH] [0: CMY/ 1: CMKY/ 2: HSI]" << endl;
    break;
  }
  }

  return 0;
}

Mat BGR_to_CMY(Mat bgrMat) {
  Mat cmyMat(bgrMat.rows, bgrMat.cols, CV_8UC3);

  for (uint16_t i = 0; i < bgrMat.rows; i++) {
    for (uint16_t j = 0; j < bgrMat.cols; j++) {
      Vec3b current_BGR_pixel = bgrMat.at<Vec3b>(i, j);

      double normalized_BGR_pixel[3] = {(double)current_BGR_pixel[0] / 255,
                                        (double)current_BGR_pixel[1] / 255,
                                        (double)current_BGR_pixel[2] / 255};

      double normalized_CMY_pixel[3] = {1 - normalized_BGR_pixel[0],
                                        1 - normalized_BGR_pixel[1],
                                        1 - normalized_BGR_pixel[2]};

      Vec3b current_CMY_pixel(normalized_CMY_pixel[0] * 255,
                              normalized_CMY_pixel[1] * 255,
                              normalized_CMY_pixel[2] * 255);

      // cout << current_CMY_pixel << endl;

      cmyMat.at<Vec3b>(i, j) = current_CMY_pixel;
    }
  }
  return cmyMat;
}

Mat BGR_to_CMYK(Mat bgrMat) {
  Mat cmykMat(bgrMat.rows, bgrMat.cols, CV_8UC4);

  for (uint16_t i = 0; i < bgrMat.rows; i++) {
    for (uint16_t j = 0; j < bgrMat.cols; j++) {
      Vec3b current_BGR_pixel = bgrMat.at<Vec3b>(i, j);

      double normalized_BGR_pixel[3] = {(double)current_BGR_pixel[0] / 255,
                                        (double)current_BGR_pixel[1] / 255,
                                        (double)current_BGR_pixel[2] / 255};

      double normalized_CMY_pixel[3] = {1 - normalized_BGR_pixel[2],
                                        1 - normalized_BGR_pixel[1],
                                        1 - normalized_BGR_pixel[0]};

      Vec3b current_CMY_pixel(normalized_CMY_pixel[0] * 255,
                              normalized_CMY_pixel[1] * 255,
                              normalized_CMY_pixel[2] * 255);

      double normalized_K =
          min(min(normalized_CMY_pixel[0], normalized_CMY_pixel[1]),
              normalized_CMY_pixel[2]);

      Vec4b current_CMYK_pixel(
          ((normalized_CMY_pixel[0] - normalized_K) / (1 - normalized_K)) * 255,
          ((normalized_CMY_pixel[1] - normalized_K) / (1 - normalized_K)) * 255,
          ((normalized_CMY_pixel[2] - normalized_K) / (1 - normalized_K)) * 255,
          normalized_K * 255);

      // cout << current_CMY_pixel << endl;

      cmykMat.at<Vec4b>(i, j) = current_CMYK_pixel;
    }
  }
  return cmykMat;
}

Mat BGR_to_HSI(Mat bgrMat) {
  Mat hsiMat(bgrMat.size(), CV_8UC3);

  for (uint16_t i = 0; i < bgrMat.rows; i++) {
    for (uint16_t j = 0; j < bgrMat.cols; j++) {
      double p[3] = {(double)bgrMat.at<Vec3b>(i, j)[BLUE],
                     (double)bgrMat.at<Vec3b>(i, j)[GREEN],
                     (double)bgrMat.at<Vec3b>(i, j)[RED]};

      double nP[3] = {p[BLUE] / 255, p[GREEN] / 255, p[RED] / 255};

      double theta =
          acos((0.5 * ((nP[RED] - nP[GREEN]) + (nP[RED] - nP[BLUE])) /
                (sqrt(pow(nP[RED] - nP[GREEN], 2) +
                      ((nP[RED] - nP[BLUE]) * (nP[GREEN] - nP[BLUE]))))));

      double hue = nP[BLUE] <= nP[GREEN] ? theta : 360 - theta;
      double saturation = 1 - ((3 / (nP[RED] + nP[GREEN] + nP[BLUE])) *
                               min(min(nP[RED], nP[GREEN]), nP[BLUE]));
      double intensity = (nP[RED] + nP[GREEN] + nP[BLUE]) / 3;

      // cout << hue << " " << saturation << " " << intensity << endl;

      // Interpolacao linear p/ poder ver o hue de 0-255 (uint8_t) ao inves de
      // 0-360
      hue = (hue - 0) / (360 - 0);
      hue = 0 + (255 - 0) * hue;
      hsiMat.at<Vec3b>(i, j) = Vec3b(hue, saturation * 255, intensity * 255);

      cout << hue << " " << saturation << " " << intensity << endl;
    }
  }

  return hsiMat;
}
