// https://learnopencv.com/color-spaces-in-opencv-cpp-python/

#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv)
{
    cv::Mat img = cv::imread("/home/jacob/Documents/3. Semester/Machine Vision/Machine-vision/1. lektion/imgs/BabyFood-Sample1.jpg");

    cv::Mat imgLAB;
    cv::cvtColor(img, imgLAB, cv::COLOR_BGR2Lab);

    cv::Mat imgYCB;
    cv::cvtColor(img, imgYCB, cv::COLOR_BGR2YCrCb);

    cv::Mat imgHSV;
    cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

    // Pixel value of extraction color
    cv::Vec3b bgrPixel(34, 18, 165);
    // Create Mat object from vector since cvtColor accepts a Mat object
    Mat3b bgr (bgrPixel);

    //Convert pixel values to other color spaces.
    Mat3b hsv,ycb,lab;
    cvtColor(bgr, ycb, COLOR_BGR2YCrCb);
    cvtColor(bgr, hsv, COLOR_BGR2HSV);
    cvtColor(bgr, lab, COLOR_BGR2Lab);
    //Get back the vector from Mat
    Vec3b hsvPixel(hsv.at<Vec3b>(0,0));
    Vec3b ycbPixel(ycb.at<Vec3b>(0,0));
    Vec3b labPixel(lab.at<Vec3b>(0,0));

    // Threshold for extraction color
    int thresh = 30;

    // Min and max for BGR based on threshold
    cv::Scalar minBGR = cv::Scalar(bgrPixel.val[0] - thresh, bgrPixel.val[1] - thresh, bgrPixel.val[2] - thresh);
    cv::Scalar maxBGR = cv::Scalar(bgrPixel.val[0] + thresh, bgrPixel.val[1] + thresh, bgrPixel.val[2] + thresh);

    // Create mask based on min and max values and produce result img
    cv::Mat maskBGR, resultBGR;
    cv::inRange(img, minBGR, maxBGR, maskBGR);
    cv::bitwise_and(img, img, resultBGR, maskBGR);

    // Min and max for HSV based on threshold
    cv::Scalar minHSV = cv::Scalar(hsvPixel.val[0] - thresh, hsvPixel.val[1] - thresh, hsvPixel.val[2] - thresh);
    cv::Scalar maxHSV = cv::Scalar(hsvPixel.val[0] + thresh, hsvPixel.val[1] + thresh, hsvPixel.val[2] + thresh);

    // Create mask based on min and max values and produce result img
    cv::Mat maskHSV, resultHSV;
    cv::inRange(imgHSV, minHSV, maxHSV, maskHSV);
    cv::bitwise_and(imgHSV, imgHSV, resultHSV, maskHSV);

    // Min and max for YCB based on threshold
    cv::Scalar minYCB = cv::Scalar(ycbPixel.val[0] - thresh, ycbPixel.val[1] - thresh, ycbPixel.val[2] - thresh);
    cv::Scalar maxYCB = cv::Scalar(ycbPixel.val[0] + thresh, ycbPixel.val[1] + thresh, ycbPixel.val[2] + thresh);

    // Create mask based on min and max values and produce result img
    cv::Mat maskYCB, resultYCB;
    cv::inRange(imgYCB, minYCB, maxYCB, maskYCB);
    cv::bitwise_and(imgYCB, imgYCB, resultYCB, maskYCB);

    // Min and max for LAB based on threshold
    cv::Scalar minLAB = cv::Scalar(labPixel.val[0] - thresh, labPixel.val[1] - thresh, labPixel.val[2] - thresh);
    cv::Scalar maxLAB = cv::Scalar(labPixel.val[0] + thresh, labPixel.val[1] + thresh, labPixel.val[2] + thresh);

    // Create mask based on min and max values and produce result img
    cv::Mat maskLAB, resultLAB;
    cv::inRange(imgLAB, minLAB, maxLAB, maskLAB);
    cv::bitwise_and(imgLAB, imgLAB, resultLAB, maskLAB);

    // Show results
    cv::imshow("IMG", img);
    cv::imshow("Result BGR", resultBGR);
    cv::imshow("Result HSV", resultHSV);
    cv::imshow("Result YCB", resultYCB);
    cv::imshow("Output LAB", resultLAB);

    // Wait for any keystroke
    cv::waitKey(0);
    return 0;
}
