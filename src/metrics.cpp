#include <iostream> 
#include <math.h>
#include <cmath>
#include <opencv2/opencv.hpp>

double MSE(cv::Mat reconstructed, cv::Mat original) {
    if (reconstructed.empty()) {
        std::cout << "The reconstructed image is empty, please check your configurations!\n";
        return INT64_MAX;
    }
    if (original.empty()) {
        std::cout << "The original image is empty, please check your configurations!\n";
        return INT64_MAX;
    }
    if (original.size() != reconstructed.size()) {
        std::cout << "The sizes of the images don't match, the original image is of size ";
        std::cout <<  original.size().height << " x " << original.size().width << " and ";
        std::cout << "the reconstructed image is of size ";
        std::cout <<  reconstructed.size().height << " x " << reconstructed.size().width << "\n";
        return INT64_MAX;
    }
    int M = original.size().height, N = original.size().width;
    float mse{0};

    if (original.channels() == 1) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                uchar delta = original.at<uchar>(i, j) - reconstructed.at<uchar>(i, j);
                mse += delta * delta;
            }
        }
    } else if (original.channels() == 3) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                cv::Vec3b o_color = original.at<cv::Vec3b>(i, j);
                uchar o_blue = o_color[0];
                uchar o_green = o_color[1];
                uchar o_red = o_color[2];

                cv::Vec3b r_color = reconstructed.at<cv::Vec3b>(i, j);
                uchar r_blue = r_color[0];
                uchar r_green = r_color[1];
                uchar r_red = r_color[2];

                mse += pow(o_blue - r_blue, 2) + pow(o_green - r_green, 2) + pow(o_red - r_red, 2);
            }
        }
    }
    mse /= (M * N);
    return mse;
}

double SNR(cv::Mat reconstructed, cv::Mat original) {
    if (reconstructed.empty()) {
        std::cout << "The reconstructed image is empty, please check your configurations!\n";
        return INT64_MAX;
    }
    if (original.empty()) {
        std::cout << "The original image is empty, please check your configurations!\n";
        return INT64_MAX;
    }
    if (original.size() != reconstructed.size()) {
        std::cout << "The sizes of the images don't match, the original image is of size ";
        std::cout <<  original.size().height << " x " << original.size().width << " and ";
        std::cout << "the reconstructed image is of size ";
        std::cout <<  reconstructed.size().height << " x " << reconstructed.size().width << "\n";
        return INT64_MAX;
    }
    int M = original.size().height, N = original.size().width;
    float sse{0}, ssq{0};

    if (original.channels() == 1) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                uchar delta = original.at<uchar>(i, j) - reconstructed.at<uchar>(i, j);
                sse += delta * delta;
                ssq += pow(original.at<uchar>(i, j), 2);
            }
        }
    } else if (original.channels() == 3) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                cv::Vec3b o_color = original.at<cv::Vec3b>(i, j);
                uchar o_blue = o_color[0];
                uchar o_green = o_color[1];
                uchar o_red = o_color[2];

                cv::Vec3b r_color = reconstructed.at<cv::Vec3b>(i, j);
                uchar r_blue = r_color[0];
                uchar r_green = r_color[1];
                uchar r_red = r_color[2];

                sse += pow(o_blue - r_blue, 2) + pow(o_green - r_green, 2) + pow(o_red - r_red, 2);
                ssq += o_blue * o_blue + o_green * o_green + o_red * o_red;
            }
        }
    }
    return 20 * log10(ssq/sse);
}

double PSNR(cv::Mat reconstructed, cv::Mat original) {
    if (reconstructed.empty()) {
        std::cout << "The reconstructed image is empty, please check your configurations!\n";
        return INT64_MAX;
    }
    if (original.empty()) {
        std::cout << "The original image is empty, please check your configurations!\n";
        return INT64_MAX;
    }
    if (original.size() != reconstructed.size()) {
        std::cout << "The sizes of the images don't match, the original image is of size ";
        std::cout <<  original.size().height << " x " << original.size().width << " and ";
        std::cout << "the reconstructed image is of size ";
        std::cout <<  reconstructed.size().height << " x " << reconstructed.size().width << "\n";
        return INT64_MAX;
    }
    int M = original.size().height, N = original.size().width;
    float sse{0};

    if (original.channels() == 1) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                uchar delta = original.at<uchar>(i, j) - reconstructed.at<uchar>(i, j);
                sse += delta * delta;
            }
        }
    } else if (original.channels() == 3) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                cv::Vec3b o_color = original.at<cv::Vec3b>(i, j);
                uchar o_blue = o_color[0];
                uchar o_green = o_color[1];
                uchar o_red = o_color[2];

                cv::Vec3b r_color = reconstructed.at<cv::Vec3b>(i, j);
                uchar r_blue = r_color[0];
                uchar r_green = r_color[1];
                uchar r_red = r_color[2];

                sse += pow(o_blue - r_blue, 2) + pow(o_green - r_green, 2) + pow(o_red - r_red, 2);
            }
        }
    }
    return 20 * log10((255 * 255 * M * N)/sse);
}