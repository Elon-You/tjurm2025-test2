#include "impls.h"
#include <opencv2/opencv.hpp>


cv::Mat my_resize(const cv::Mat& input, float scale) {
    /**
     * 要求：
     *      实现resize算法，只能使用基础的语法，比如说for循环，Mat的基本操作。不能
     * 用cv::resize。resize算法的内容自行查找学习，不是很难。
     * 
     * 提示：
     * 无。
     * 
     * 通过条件：
     * 运行测试点，你的结果跟答案长的差不多就行。
     */
    int new_rows = static_cast<int>(input.rows * scale);
    int new_cols = static_cast<int>(input.cols * scale);

    cv::Mat output = cv::Mat::zeros(new_rows, new_cols, input.type());

    float row_scale = static_cast<float>(input.rows) / new_rows;
    float col_scale = static_cast<float>(input.cols) / new_cols;

    for (int i = 0; i < new_rows; i++) {
        for (int j = 0; j < new_cols; j++) {
            float src_x = j * col_scale;
            float src_y = i * row_scale;

            int x = static_cast<int>(src_x);
            int y = static_cast<int>(src_y);

            if (x >= input.cols - 1) x = input.cols - 2;
            if (y >= input.rows - 1) y = input.rows - 2;

            float dx = src_x - x;
            float dy = src_y - y;

            for (int c = 0; c < input.channels(); c++) {
                float top_left = input.at<cv::Vec3b>(y, x)[c];
                float top_right = input.at<cv::Vec3b>(y, x + 1)[c];
                float bottom_left = input.at<cv::Vec3b>(y + 1, x)[c];
                float bottom_right = input.at<cv::Vec3b>(y + 1, x + 1)[c];

                float top = top_left + dx * (top_right - top_left);
                float bottom = bottom_left + dx * (bottom_right - bottom_left);

                output.at<cv::Vec3b>(i, j)[c] = static_cast<uchar>(top + dy * (bottom - top));
            }
        }
    }

    return output;
}