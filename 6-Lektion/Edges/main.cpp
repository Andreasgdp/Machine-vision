#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

// Driver code
int main(int argc, char** argv)
{
    // Read the image file as
    cv::Mat image = cv::imread("../imgs/rocket.jpg", cv::IMREAD_GRAYSCALE);

    // Error Handling
    if (image.empty()) {
        cout << "Image File Not Found" << endl;

        // wait for any key press
        cin.get();
        return -1;
    }

    // Canny step 1. Gaussian smoothing
    cv::Mat smoothed_image;
    cv::Mat kernal(3, 3, CV_32F);
    cv::GaussianBlur(image, smoothed_image, kernal.size(), 0);

    // Canny step 2. Magnitude and direction
    cv::Mat horizontal_derivative, vertical_derivative;
    Sobel(image, horizontal_derivative, CV_32F,1,0);
    Sobel(image, vertical_derivative, CV_32F,0,1);
    cv::Mat abs_gradient, l2norm_gradient, orientation;
    abs_gradient = abs(horizontal_derivative) + abs(vertical_derivative);
    cv::cartToPolar(horizontal_derivative, vertical_derivative, l2norm_gradient, orientation, true);
    // https://shimat.github.io/opencvsharp_docs/html/d8325d06-b4c4-2e2e-9eec-dee08f6e8098.htm

    // Canny step 3. Zero out (non-maxima suppression)
    cv::Mat zero_out;
    for (int i = 0; i < orientation.cols; i++) {
        for (int j = 0; j < orientation.rows; j++) {
            cout << "orientation cols: " << orientation.cols << endl;
            cout << "orientation rows: " << orientation.rows << endl;
            cout << "l2norm_gradient cols: " << l2norm_gradient.cols << endl;
            cout << "l2norm_gradient rows: " << l2norm_gradient.rows << endl;
            float dir = orientation.at<float>(i, j);
            float grad = l2norm_gradient.at<float>(i, j);
            float gradFront, gradBack;
            // Between 337.5 and 360 or 0 and 22.5 or 157.5 and 202.5
            if (dir > 360 - 45 / 2 && dir <= 360
                || dir >= 0 && dir < 45 / 2
                || dir > 180 - 45 / 2 && dir < 180 + 45 / 2) {
                gradFront = l2norm_gradient.at<float>(i + 1, j);
                gradBack = l2norm_gradient.at<float>(i - 1, j);
                cout << "gradBack: " << gradBack << endl;
            // Between
            } else if (dir >= 45 / 2 && dir < 45 / 2 + 45
                       || dir >= 180 + 45 / 2 && dir < 180 + 45 / 2 + 45) {
                gradFront = l2norm_gradient.at<float>(i + 1, j - 1);
                gradBack = l2norm_gradient.at<float>(i - 1, j + 1);
            // Between
            } else if (dir >= 45 / 2 + 45  && dir < 45 / 2 + 45 + 45
                       || dir >= 180 + 45 / 2 + 45 && dir < 180 + 45 / 2 + 45 + 45) {
                gradFront = l2norm_gradient.at<float>(i, j - 1);
                gradBack = l2norm_gradient.at<float>(i, j + 1);
            // Between
            } else if (dir >= 45 / 2 + 45 + 45  && dir < 45 / 2 + 45 + 45 + 45
                       || dir >= 180 + 45 / 2 + 45 + 45 && dir < 180 + 45 / 2 + 45 + 45 + 45) {
                gradFront = l2norm_gradient.at<float>(i - 1, j - 1);
                gradBack = l2norm_gradient.at<float>(i + 1, j + 1);
            } else {
                cout << "Not in spaghetti code, dumbass!" << endl;
            }

            if (grad < gradFront || grad < gradBack) {
                zero_out.at<float>(i, j) = 0;
                cout << "Amst here too!" << endl;
            } else {
                zero_out.at<float>(i, j) = grad;
                cout << "Amst here too!" << endl;
            }
            //cout << l2norm_gradient.at<float>(i, j) << endl;
        }
    }



    // Canny step 4. Track (Hysteresis thresholding)

    // Canny step 5. Keep


    // Show Image
    cv::imshow("Image", image);
    cv::imshow("smoothed_image", smoothed_image);

    cv::imshow("horizontal_derivative", horizontal_derivative);
    cv::imshow("vertical_derivative", vertical_derivative);

    //cv::imshow("abs_gradient", abs_gradient);
    //cv::imshow("l2norm_gradient", l2norm_gradient);
    //cv::imshow("orientation", orientation);

    cv::imshow("zero_out", zero_out);

    // Wait for any keystroke
    cv::waitKey(0);
    return 0;
}


