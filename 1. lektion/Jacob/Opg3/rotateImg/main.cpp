#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

// Driver code
int main(int argc, char** argv)
{
    // Read the image file as
    // imread("default.jpg");
    cv::Mat image = cv::imread("/home/jacob/Documents/3. Semester/Machine Vision/Machine-vision/1. lektion/imgs/legoHouse.jpg",
                               cv::IMREAD_COLOR);

    // Error Handling
    if (image.empty()) {
        cout << "Image File Not Found" << endl;

        // wait for any key press
        cin.get();
        return -1;
    }

    cv::rotate(image, image, cv::ROTATE_90_CLOCKWISE);

    // Show Image inside a window with
    // the name provided
    cv::imshow("Window Name", image);

    // Wait for any keystroke
    cv::waitKey(0);
    return 0;
}