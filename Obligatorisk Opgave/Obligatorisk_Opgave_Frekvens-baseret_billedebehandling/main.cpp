#include <iostream>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;


int main() {
    // --------------- Edge detection (canny) --------------
    // Reading image
    Mat img = imread("../billede_noiseFree.png");
    // Display original image
    imshow("Original Image", img);

    // Convert to graycsale
    Mat img_gray;
    cvtColor(img, img_gray, COLOR_BGR2GRAY);
    // Blur the image for better edge detection
    Mat img_blur;
    GaussianBlur(img_gray, img_blur, Size(3,3), 0);

    // Canny edge detection
    Mat edges;
    Canny(img_blur, edges, 100, 200, 3, false);
    // Display canny edge detected image
    imshow("Canny edge detection", edges);

    // --------------- Hough Akkumulator ---------------
    Mat houghSpace = Mat::zeros(edges.size(), CV_32F);
    vector<vector<unsigned int>> pixelVal;
    for (unsigned int i = 0; i < edges.rows; i++) {
        for (unsigned int j = 0; j < edges.cols; j++) {
            uchar pixel = edges.at<uchar>(i, j);
            if (pixel == 255){
                Mat temp = Mat::zeros(edges.size(), CV_32F);
                circle(temp, Point(j,i), 32, Scalar(2, 2, 2), 1);
                cv::add(temp, houghSpace, houghSpace);
            }
        }
    }
    Mat visible_houghSpace;
    convertScaleAbs(houghSpace, visible_houghSpace);
    imshow("Hough circle detection", visible_houghSpace);

    // --------------- Cirkel Position ---------------
    double minVal;
    double maxVal;
    Point minLoc;
    Point maxLoc;

    minMaxLoc(visible_houghSpace, &minVal, &maxVal, &minLoc, &maxLoc );

    cout << "Max coords: " << maxLoc << endl;

    Mat img_final = img;
    circle(img_final, maxLoc, 1, Scalar(0,255,0), 1, LINE_AA);
    circle(img_final, maxLoc, 32, Scalar(0, 0, 255), 1, LINE_AA);
    imshow("img_final", img_final);

    waitKey(0);
    destroyAllWindows();
    return 0;
}

