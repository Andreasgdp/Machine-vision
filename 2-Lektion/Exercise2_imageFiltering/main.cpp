#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>

using namespace std;

int median(vector<int> &v)
{
    size_t n = v.size() / 2;
    nth_element(v.begin(), v.begin()+n, v.end());
    return v[n];
}

cv::Mat add_padding(cv::Mat input, int padding_top_bot, int padding_sides) {
    cv::Mat padded_image;
    cv::copyMakeBorder(input, padded_image, padding_top_bot, padding_top_bot, padding_sides, padding_sides, CV_HAL_BORDER_REPLICATE);
    return padded_image;
}

void median_filter(cv::Mat input, cv::Mat output) {
    cv::Mat padded_image = add_padding(input, 1, 1);

    // Iterate over all pixels in the image
    int n = 9;
    int k = (3-1)/2;
    int count = 0;
    for (size_t r = 0; r < input.rows; r++) {
        for (size_t c = 0; c < input.cols; c++) {
            vector<int> vec;
            for (int i = -k; i <= k ; i++) {
                for (int j = -k; j <= k; j++) {
                    vec.push_back(padded_image.at<uchar>(k+r-i,k+c-j));
                }
            }
            output.at<uchar>(r,c) = cv::saturate_cast<uchar>(median(vec));
        }
    }
}

void linear_filter(cv::Mat input, cv::Mat kernel, cv::Mat& output) {
    cv::Mat padded_image = add_padding(input, floor(kernel.rows / 2.0), floor(kernel.cols / 2.0));

    CV_Assert(input.type()==CV_8UC1);
    CV_Assert(kernel.type()==CV_32FC1);
    CV_Assert(kernel.rows%2==1 && kernel.cols%2==1 && kernel.rows == kernel.cols);

    int k = (kernel.rows - 1) / 2;

    output = cv::Mat(input.rows, input.cols, CV_8UC1);
    // Double for-loop to iterate over all pixels in the output image
    for(int r=0; r<input.rows; r++){
       for(int c=0; c<input.cols; c++){
           // Double for-loop to implement convolution operation
           double sum = 0;
           for(int i=-k; i<=k; i++){
               for(int j=-k; j<=k; j++){
                   sum += input.at<uchar>(k+r-i, k+c-j)*kernel.at<float>(k+i,k+j); //index of kernel center in (2k+1)(2k+1) is (k,k)
               }
           }
           output.at<uchar>(r,c) = cv::saturate_cast<uchar>(sum);
       }
   }
}

// Driver code
int main(int argc, char** argv)
{
    // Read the image file as
    cv::Mat image = cv::imread("../imgs/legoHouse_gaussian.jpg", cv::IMREAD_GRAYSCALE);

    // Error Handling
    if (image.empty()) {
        cout << "Image File Not Found" << endl;

        // wait for any key press
        cin.get();
        return -1;
    }

    cv::Mat median_out_img(image.rows, image.cols, CV_8UC1);
    cv::Mat linear_out_img(image.rows, image.cols, CV_8UC1);
    cv::Mat linear_out_img_gaussian(image.rows, image.cols, CV_8UC1);

    // Generate uniform kernel 1/9
    int kernelSize = 3;
    cv::Mat kernel_uniform(kernelSize, kernelSize, CV_32FC1);
    for(int i = 0; i < kernel_uniform.rows; i++){
       for(int j = 0; j < kernel_uniform.cols; j++){
           kernel_uniform.at<float>(i,j) = 1.0 / (kernelSize * kernelSize);
       }
    }

    // Generate Gaussian kernel (very good code)
    int kernelSize_gaussian = 5;
    cv::Mat kernel_gaussian(kernelSize_gaussian, kernelSize_gaussian, CV_32FC1);
    kernel_gaussian.at<float>(0,0) = 0;
    kernel_gaussian.at<float>(0,1) = 1;
    kernel_gaussian.at<float>(0,2) = 2;
    kernel_gaussian.at<float>(0,3) = 1;
    kernel_gaussian.at<float>(0,4) = 0;
    kernel_gaussian.at<float>(1,0) = 1;
    kernel_gaussian.at<float>(1,1) = 3;
    kernel_gaussian.at<float>(1,2) = 5;
    kernel_gaussian.at<float>(1,3) = 3;
    kernel_gaussian.at<float>(1,4) = 1;
    kernel_gaussian.at<float>(2,0) = 2;
    kernel_gaussian.at<float>(2,1) = 5;
    kernel_gaussian.at<float>(2,2) = 9;
    kernel_gaussian.at<float>(2,3) = 5;
    kernel_gaussian.at<float>(2,4) = 2;
    kernel_gaussian.at<float>(3,0) = 1;
    kernel_gaussian.at<float>(3,1) = 3;
    kernel_gaussian.at<float>(3,2) = 5;
    kernel_gaussian.at<float>(3,3) = 3;
    kernel_gaussian.at<float>(3,4) = 1;
    kernel_gaussian.at<float>(4,0) = 0;
    kernel_gaussian.at<float>(4,1) = 1;
    kernel_gaussian.at<float>(4,2) = 2;
    kernel_gaussian.at<float>(4,3) = 1;
    kernel_gaussian.at<float>(4,4) = 0;

    median_filter(image, median_out_img);
    linear_filter(image, kernel_uniform, linear_out_img);
    linear_filter(image, kernel_gaussian, linear_out_img_gaussian);

    // Show Image inside a window with
    // the name provided
    cv::imshow("Image", image);
    cv::imshow("Median", median_out_img);
    cv::imshow("Linear", linear_out_img);
    cv::imshow("Linear_gaussian", linear_out_img);

    // Wait for any keystroke
    cv::waitKey(0);
    return 0;
}


