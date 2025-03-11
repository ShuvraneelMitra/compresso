#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Read an image from a file
    cv::Mat image = cv::imread("/home/shuvraneel-mitra/Desktop/Multimedia Compression Techniques/image.jpg");

    if (image.empty()) {
        std::cout << "Could not open or find the image!" << std::endl;
        return -1;
    }

    // Check if the image is colored or grayscale
    if (image.channels() == 1) {
        // Grayscale image: iterate through each pixel
        for (int i = 0; i < image.rows; i++) {
            for (int j = 0; j < image.cols; j++) {
                // Access each pixel's intensity value (uint8_t)
                uchar pixelValue = image.at<uchar>(i, j);
                // Do something with the pixel value (e.g., print)
                std::cout << "Pixel at (" << i << ", " << j << "): " << (int)pixelValue << std::endl;
            }
        }
    } else if (image.channels() == 3) {
        // Color image: iterate through each pixel
        for (int i = 0; i < image.rows; i++) {
            for (int j = 0; j < image.cols; j++) {
                // Access each pixel's BGR values
                cv::Vec3b color = image.at<cv::Vec3b>(i, j);
                uchar blue = color[0];
                uchar green = color[1];
                uchar red = color[2];
                // Do something with the pixel values (e.g., print)
                std::cout << "Pixel at (" << i << ", " << j << "): B=" << (int)blue
                          << " G=" << (int)green << " R=" << (int)red << std::endl;
            }
        }
    }

    return 0;
}
