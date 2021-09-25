#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

// Driver code
int main(int argc, char** argv)
{
    cv::Mat image = cv::imread("../imgs/licencePlate1.png",
                               cv::IMREAD_GRAYSCALE);

    // Error Handling
    if (image.empty()) {
        std::cout << "Image File Not Found" << std::endl;

        // wait for any key press
        std::cin.get();
        return -1;
    }

    cv::Mat binary_image;
    cv::threshold(image, binary_image, 100, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    cv::bitwise_not(binary_image, binary_image);

    // Morphological operations
    cv::Mat eroded_image;
    cv::Mat structuring_element(4, 4, CV_8U, cv::Scalar(1));
    cv::erode(binary_image, eroded_image, structuring_element);

    cv::Mat five_by_five_element(5, 5, CV_8U, cv::Scalar(1));
    cv::Mat closed_image;
    cv::morphologyEx(eroded_image, closed_image, cv::MORPH_CLOSE, five_by_five_element);

    cv::Mat structuring_element_dialte(5, 5, CV_8U, cv::Scalar(1));
    cv::Mat dilated_image;
    cv::dilate(closed_image, dilated_image, structuring_element_dialte);

    // Connected components algorithm
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(dilated_image, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);

    cv::Mat contours_image;
    cv::cvtColor(dilated_image, contours_image, cv::COLOR_GRAY2BGR);
    for (int contour = 0; (contour < contours.size()); contour++) {
        cv::Scalar colour(std::rand()&0xFF, std::rand()&0xFF, std::rand()&0xFF);
        cv::drawContours(contours_image, contours, contour, colour, cv::FILLED, 8, hierarchy);
    }

    cv::imshow("Image", image);
    cv::imshow("Binary Image", binary_image);
    cv::imshow("Eroded Image", eroded_image);
    cv::imshow("Closed Image", closed_image);
    cv::imshow("Dilated Image", dilated_image);
    cv::imshow("Contours Image", contours_image);
    cv::waitKey(0);

    return 0;
}
