#pragma once

#include <abstractopencvrunnablefilter.h>
#include <opencv2/core.hpp>

class CannyFilter : public QAbstractVideoFilter {
    Q_OBJECT

    Q_PROPERTY(int threshold READ threshold WRITE threshold NOTIFY thresholdChanged)

public:
    QVideoFilterRunnable* createFilterRunnable() override;

    int threshold() const { return m_threshold; }
    void threshold(int thr) { m_threshold = thr; }

signals:
    void thresholdChanged();

private:
    int m_threshold = 128;
};

class CannyFilterRunnable : public AbstractVideoFilterRunnable {
public:
    CannyFilterRunnable(CannyFilter* filter);
    QVideoFrame run(QVideoFrame* input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags) override;

private:
    CannyFilter* m_filter;
};
