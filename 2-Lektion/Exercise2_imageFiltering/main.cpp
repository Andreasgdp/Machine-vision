#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;

int median(vector<int> &v)
{
    size_t n = v.size() / 2;
    nth_element(v.begin(), v.begin()+n, v.end());
    return v[n];
}

cv::Mat add_padding(cv::Mat input, int pad_top, int pad_bot, int pad_left, int pad_right) {
    cv::Mat padded_image;
    cv::copyMakeBorder(input, padded_image, pad_top, pad_bot, pad_left, pad_right, CV_HAL_BORDER_REPLICATE);
    return padded_image;
}

void median_filter(cv::Mat input, cv::Mat kernal, cv::Mat output) {
    cv::Mat padded_image = add_padding(input, 1, 1, 1, 1);

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

void uniform_filter(cv::Mat input, cv::Mat kernal, cv::Mat output) {
    add_padding(input, 1, 1, 1, 1);

    //Test linear filter on src with uniform kernel
    int kernelSize = 5;
    cv::Mat kernel(kernelSize,kernelSize, CV_32FC1);
    for(int i=0; i<kernel.rows; i++){
       for(int j=0; j<kernel.cols; j++){
           kernel.at<float>(i,j) = 1.0/(kernelSize*kernelSize);
       }
    }

    CV_Assert(input.type()==CV_8UC1);
    CV_Assert(kernel.type()==CV_32FC1);
    CV_Assert(kernel.rows%2==1 && kernel.cols%2==1 && kernel.rows == kernel.cols);

    int k = (3-1)/2;
    cv::Mat temp;

    output = cv::Mat(input.rows, input.cols, CV_8UC1);
    // Double for-loop to iterate over all pixels in the output image
    for(int r=0; r<input.rows; r++){
       for(int c=0; c<input.cols; c++){
           // Double for-loop to implement convolution operation
           double sum = 0;
           for(int i=-k; i<=k; i++){
               for(int j=-k; j<=k; j++){
                   sum += temp.at<uchar>(k+r-i, k+c-j)*kernel.at<float>(k+i,k+j); //index of kernel center in (2k+1)(2k+1) is (k,k)
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
    cv::Mat image = cv::imread("../imgs/test_saltpepper.png", cv::IMREAD_GRAYSCALE);
    cv::Mat kernel(3, 3, CV_32FC1);
    cv::Mat median_out_img(image.rows, image.cols, CV_8UC1);
    cv::Mat uniform_out_img(image.rows, image.cols, CV_8UC1);

    median_filter(image, kernel, median_out_img);
    uniform_filter(image, kernel, median_out_img);

    // Error Handling
    if (image.empty()) {
        cout << "Image File Not Found" << endl;

        // wait for any key press
        cin.get();
        return -1;
    }

    // Show Image inside a window with
    // the name provided
    cv::imshow("Median", median_out_img);
    cv::imshow("Unifrom", uniform_out_img);

    // Wait for any keystroke
    cv::waitKey(0);
    return 0;
}


