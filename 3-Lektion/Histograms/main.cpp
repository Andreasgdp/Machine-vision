#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

void showHist(cv::Mat grayImage, string windowName) {
    CV_Assert(grayImage.type()==CV_8UC1);
    int const histSize = 256;
    float range[] = {0, histSize};
    const float* histRange = {range};
    bool uniform = true;
    bool accumulate = false;

    cv::Mat hist;
    cv::calcHist(&grayImage, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);

    //Initialize histogram image
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );
    cv::Mat histImage( hist_h, hist_w, CV_8UC3, cv::Scalar( 0,0,0) );

    // Normalize the result to [ 0, histImage.rows ]
    cv::normalize(hist, hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );

    // Draw line between each (bin,value)
    for( int i = 1; i < histSize; i++ ){
      cv::line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1)) ) ,
                       cv::Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ),
                       cv::Scalar( 255, 0, 0), 2, 8, 0  );
    }

    // Display
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
    cv::imshow(windowName, histImage);

}

cv::Mat calcHist(cv::Mat grayImage) {
    CV_Assert(grayImage.type()==CV_8UC1);
    int const histSize = 256;
    float range[] = {0, histSize};
    const float* histRange = {range};
    bool uniform = true;
    bool accumulate = false;

    cv::Mat hist;
    cv::calcHist(&grayImage, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);
    return hist;
}

cv::Mat equalisation(cv::Mat image) {
    CV_Assert(image.type()==CV_8UC1);
    uchar pixels_so_far = 0;
    uchar num_pixels = image.rows * image.cols;
    uchar output = 0;
    cv::Mat h = calcHist(image);

    // Normalize the result to [ 0, histImage.rows ]
    cv::normalize(h, h, 0, image.rows, cv::NORM_MINMAX, -1, cv::Mat() );

    cv::Mat LUT(1, 255, CV_8UC1);

    for (int i = 0; i <= 255; i++) {
        pixels_so_far = pixels_so_far + h.at<uchar>(i);
        output = 255 * pixels_so_far / num_pixels;
        LUT.at<uchar>(i) = output;
    }

    // Apply the lookup table LUT(x) to the image
    cv::Mat eq_image(image.rows, image.cols, CV_8UC1);
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            eq_image.at<uchar>(i,j) = LUT.at<uchar>(image.at<uchar>(i,j));
        }
    }
    return eq_image;
}

// Driver code
int main(int argc, char** argv)
{
    // Read the image file
    cv::Mat image = cv::imread("../imgs/legoHouse.jpg", cv::IMREAD_COLOR);

    // Error Handling
    if (image.empty()) {
        cout << "Image File Not Found" << endl;

        // wait for any key press
        cin.get();
        return -1;
    }

    cv::Mat image_grey;
    cv::cvtColor(image, image_grey, cv::COLOR_BGR2GRAY);

    // Show Image
    cv::imshow("no_iq image", image_grey);
    cv::imshow("eq image", equalisation(image_grey));

    showHist(image_grey, "No_eq");
    showHist(equalisation(image_grey), "with_eq");

    cv::waitKey(0);

    return 0;
}
