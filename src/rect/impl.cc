#include "impls.h"
#include <opencv2/opencv.hpp>


std::pair<cv::Rect, cv::RotatedRect> get_rect_by_contours(const cv::Mat& input) {
    /**
     * 要求：
     * 使用findCountours函数找出输入图像（彩色图像）中的矩形轮廓，并且返回它的外接矩形，以及
     * 最小面积外接矩形。所需要的函数自行查找。
     * 
     * 通过条件：
     * 运行测试点，你找到的矩形跟答案一样就行。
    */
    std::pair<cv::Rect, cv::RotatedRect> res;
    // IMPLEMENT YOUR CODE HERE
    cv::Mat gray, binary;

    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);

    cv::threshold(gray, binary, 100, 255, cv::THRESH_BINARY);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(binary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    for (const auto& contour : contours) {
        cv::Rect bounding_rect = cv::boundingRect(contour);
        
        cv::RotatedRect min_area_rect = cv::minAreaRect(contour);
        
        res = {bounding_rect, min_area_rect};
    }
    return res;
}