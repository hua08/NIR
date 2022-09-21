#ifndef CHART_H
#define CHART_H

#include <QGraphicsView>

class Chart : public QWidget
{
    Q_OBJECT
public:
    explicit Chart(QWidget *parent = nullptr);

signals:
    void updateUi();

protected:

public:


private:


};
#endif // CHART_H
