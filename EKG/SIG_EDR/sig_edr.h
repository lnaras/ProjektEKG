#ifndef SIG_EDR_H
#define SIG_EDR_H

#pragma once

#include <QList>
#include <QVector>
#include <QString>

#include <QsLog.h>
#include <QsLogDest.h>
#include <QDir>

#include <vector>
#include <cmath>

class sig_edr{

const QVector<double> signal_one;
const QVector<double> signal_two;

QVector<double> EDRsignal_RPeaks_one;
QVector<double> EDRsignal_RPeaks_two;
QVector<double> EDRsignal_Waves;
std::vector<double> EDRsignal;

QVector<double> Integrals_one;
QVector<double> Integrals_two;


public:
    sig_edr(const QVector<double> &signal_one,
            const QVector<double> &signal_two);

    sig_edr(const QVector<double> &signal_one,
            const QVector<double>::const_iterator &RPeaksIterators_one,
            const QVector<double> &signal_two,
            const QVector<double>::const_iterator &RPeaksIterators_two
            );

    sig_edr(const QVector<double> &signal_one,
            const QVector<double>::const_iterator &QRSonsetIterators_one,
            const QVector<double>::const_iterator &QRSendIterators_one,
            const QVector<double> &signal_two,
            const QVector<double>::const_iterator &QRSonsetIterators_two,
            const QVector<double>::const_iterator &QRSendIterators_two
            );

    void new_RPeaks_signal(int signal_num,
                           const QVector<double>::const_iterator &RPeaksIterators
                           );

    void new_Waves_signal(const QVector<double>::const_iterator &QRSonsetIterators_one,
                          const QVector<double>::const_iterator &QRSendIterators_one,
                          const QVector<double>::const_iterator &QRSonsetIterators_two,
                          const QVector<double>::const_iterator &QRSendIterators_two
                          );

    QVector<double>* retrieveEDR_QVec(int EDR_type, int signal_num);
    std::vector<double>* retrieveEDR_StdVec(int EDR_type, int signal_num);

private:

    double integral(QVector<double> &value);

    void calculate_signal_from_QRS(const QVector<double> &QRSIntegrals_one,
                                   const QVector<double> &QRSIntegrals_two);
};

#endif //SIG_EDR_H
