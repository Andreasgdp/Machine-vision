#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;

// Driver code
int main(int argc, char** argv)
{
    cv::Mat image = cv::imread("../chessboard.jpg", cv::IMREAD_GRAYSCALE);

    // Error Handling
    if (image.empty()) {
        std::cout << "Image File Not Found" << std::endl;

        // wait for any key press
        std::cin.get();
        return -1;
    }

    // Perspective transform
    cv::Point2f source[4], destination[4];
    source[0] = cv::Point(302, 167);
    source[1] = cv::Point(1600, 164);
    source[2] = cv::Point(51, 1155);
    source[3] = cv::Point(1868, 1148);
    destination[0] = cv::Point(0, 0);
    destination[1] = cv::Point(1200, 0);
    destination[2] = cv::Point(0, 1200);
    destination[3] = cv::Point(1200, 1200);

    cv::Mat perspective_matrix;
    cv::Mat result;
    perspective_matrix = cv::getPerspectiveTransform(source, destination);
    cv::warpPerspective(image, result, perspective_matrix, result.size());

    cv::imshow("Image", image);
    cv::imshow("result", result);


    // Projection
    const float fx = 1195.3, fy = 1195.3, cx = 717.7, cy = 543.2;
    float instrinsic_data[9] = {fx, 0, cx, 0, fy, cy, 0, 0, 1};
    cv::Mat instrinsic_mat = cv::Mat(3, 3, CV_32F, instrinsic_data);
    cout << "instrinsic_mat = " << endl << instrinsic_mat << endl << endl;

    float extrinsic_data[12] = {1, 0, 0, 0.15, 0, -1, 0, 0.2, 0, 0, -1, 1};
    cv::Mat extrinsic_mat = cv::Mat(3, 4, CV_32F, extrinsic_data);
    cout << "extrinsic_mat = " << endl << extrinsic_mat << endl << endl;

    float point_data[4] = {0.05, 0.05, 0.0, 1};
    cv::Mat point_mat = cv::Mat(4, 1, CV_32F, point_data);
    cout << "point_mat = " << endl << point_mat << endl << endl;

    cv::Mat result_mat = instrinsic_mat * extrinsic_mat * point_mat;
    cout << "result_mat = " << endl << result_mat << endl << endl;
    // TODO: Fix forkert resultat (har noget med s at gøre)

    cv::waitKey(0);

    return 0;
}
