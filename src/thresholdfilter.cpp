#include "thresholdfilter.h"
#include <opencv2/imgproc.hpp>
#include <QDebug>
#include <stdexcept>
using namespace std;

QVideoFilterRunnable* ThresholdFilter::createFilterRunnable()
{
    return new ThresholdFilterRunnable(this);
}

ThresholdFilterRunnable::ThresholdFilterRunnable(ThresholdFilter* filter)
    : m_filter{filter}
{
}

QVideoFrame ThresholdFilterRunnable::run(QVideoFrame* frame, const QVideoSurfaceFormat&, QVideoFilterRunnable::RunFlags)
{
    if (!isFrameValid(frame))
    {
        qDebug() << "Frame is NOT valid";
        return QVideoFrame{};
    }

    if (!frame->map(QAbstractVideoBuffer::ReadWrite))
    {
        qDebug() << "Unable to map the videoframe in memory" << endl;
        return *frame;
    }

    try
    {
        cv::Mat frameMat, grayscale;
        videoframeToGrayscale(frame, grayscale, frameMat);

        cv::flip(grayscale, grayscale, 1);
        cv::threshold(grayscale, grayscale, m_filter->threshold(), 255.0, cv::THRESH_BINARY);

        vector<vector<cv::Point>> contours;
        vector<cv::Vec4i> hierarchy;

        grayscaleToVideoFrame(frame, grayscale, frameMat);

//        cv::findContours(grayscale, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

        //            for( int i = 0; i< contours.size(); i++ )
        //                cv::drawContours(frameMat, contours, i, cv::Scalar(255,0,0,0), 2, 8, hierarchy, 0, cv::Point());
    }
    catch(const std::exception& exc)
    {
        qDebug() << exc.what();
    }

    frame->unmap();


    return *frame;
}
