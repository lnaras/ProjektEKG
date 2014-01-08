#include "sig_edr.h"

sig_edr::sig_edr(const QVector<double> &signal_one,
                 const QVector<double> &signal_two
                ): signal_one(signal_one), signal_two(signal_two)
{}

sig_edr::sig_edr(const QVector<double> &signal_one,
                 const QVector<double>::const_iterator &RPeaksIterators_one,
                 const QVector<double> &signal_two,
                 const QVector<double>::const_iterator &RPeaksIterators_two
                 ): signal_one(signal_one), signal_two(signal_two)
{
    QVector<double>::const_iterator iterator = signal_one.begin();
    QVector<double>::const_iterator RPeaks   = RPeaksIterators_one;

    EDRsignal_RPeaks_one.clear();

    while(iterator != signal_one.end())
    {
        if(iterator == RPeaks)
        {
            EDRsignal_RPeaks_one << *iterator;
            RPeaks++;
        }
        else
            iterator++;
    }

    iterator = signal_two.begin();
    RPeaks   = RPeaksIterators_two;

    EDRsignal_RPeaks_two.clear();

    while(iterator != signal_two.end())
    {
        if(iterator == RPeaks)
        {
            EDRsignal_RPeaks_two << *iterator;
            RPeaks++;
        }
        else
            iterator++;
    }
}

sig_edr::sig_edr(const QVector<double> &signal_one,
                 const QVector<double>::const_iterator &QRSonsetIterators_one,
                 const QVector<double>::const_iterator &QRSendIterators_one,
                 const QVector<double> &signal_two,
                 const QVector<double>::const_iterator &QRSonsetIterators_two,
                 const QVector<double>::const_iterator &QRSendIterators_two
                ): signal_one(signal_one), signal_two(signal_two)
{
    QVector<double>::const_iterator iterator    = signal_one.begin();
    QVector<double>::const_iterator QRSonset    = QRSonsetIterators_one;
    QVector<double>::const_iterator QRSend      = QRSendIterators_one;
    QVector<double> QRS_Clas;

    EDRsignal_Waves.clear();

    while(iterator != signal_one.end())
    {
        if(iterator == QRSonset)
        {
            while (iterator != QRSend)
            {
                QRS_Clas << *iterator;
                iterator++;
            }
            QRS_Clas << *iterator;
            iterator++;
            QRSonset++;
            QRSend++;

            Integrals_one << integral(QRS_Clas);
            QRS_Clas.clear();
        }
        else
        {
            iterator++;
        }
    }

    iterator    = signal_two.begin();
    QRSonset    = QRSonsetIterators_two;
    QRSend      = QRSendIterators_two;

    while(iterator != signal_two.end())
    {
        if(iterator == QRSonset)
        {
            while (iterator != QRSend)
            {
                QRS_Clas << *iterator;
                iterator++;
            }
            QRS_Clas << *iterator;
            iterator++;
            QRSonset++;
            QRSend++;

            Integrals_two << integral(QRS_Clas);
            QRS_Clas.clear();
        }
        else
        {
            iterator++;
        }
    }
    calculate_signal_from_QRS(Integrals_one, Integrals_two);
}

void sig_edr::new_RPeaks_signal(int signal_num ,
                                const QVector<double>::const_iterator &RPeaksIterators
                                )
{
    QVector<double>::const_iterator iterator;
    QVector<double>::const_iterator RPeaks  = RPeaksIterators;

    signal_num %=2;
    if(signal_num == 1)
    {
        iterator = signal_one.begin();
        EDRsignal_RPeaks_one.clear();

        while(iterator != signal_one.end())
        {
            if(iterator == RPeaks)
            {
                EDRsignal_RPeaks_one << *iterator;
                RPeaks++;
            }
            else
                iterator++;
        }
    }
    else
    {
        iterator = signal_two.begin();
        EDRsignal_RPeaks_two.clear();

        while(iterator != signal_two.end())
        {
            if(iterator == RPeaks)
            {
                EDRsignal_RPeaks_two << *iterator;
                RPeaks++;
            }
            else
                iterator++;
        }

    }
}

void sig_edr::new_Waves_signal(const QVector<double>::const_iterator &QRSonsetIterators_one,
                               const QVector<double>::const_iterator &QRSendIterators_one,
                               const QVector<double>::const_iterator &QRSonsetIterators_two,
                               const QVector<double>::const_iterator &QRSendIterators_two
                               )
{
    QVector<double>::const_iterator iterator    = signal_one.begin();
    QVector<double>::const_iterator QRSonset    = QRSonsetIterators_one;
    QVector<double>::const_iterator QRSend      = QRSendIterators_one;
    QVector<double> QRS_Clas;

    Integrals_one.clear();
    Integrals_two.clear();
    EDRsignal_Waves.clear();

    while(iterator != signal_one.end())
    {
        if(iterator == QRSonset)
        {
            while (iterator != QRSend)
            {
                QRS_Clas << *iterator;
                iterator++;
            }
            QRS_Clas << *iterator;
            iterator++;
            QRSonset++;
            QRSend++;

            Integrals_one << integral(QRS_Clas);
            QRS_Clas.clear();
        }
        else
        {
            iterator++;
        }
    }

    iterator    = signal_two.begin();
    QRSonset    = QRSonsetIterators_two;
    QRSend      = QRSendIterators_two;

    while(iterator != signal_two.end())
    {
        if(iterator == QRSonset)
        {
            while (iterator != QRSend)
            {
                QRS_Clas << *iterator;
                iterator++;
            }
            QRS_Clas << *iterator;
            iterator++;
            QRSonset++;
            QRSend++;

            Integrals_two << integral(QRS_Clas);
            QRS_Clas.clear();
        }
        else
        {
            iterator++;
        }
    }
    calculate_signal_from_QRS(Integrals_one, Integrals_two);
}

QVector<double>* sig_edr::retrieveEDR_QVec(int EDR_type, int signal_num
                                           )
{
    signal_num %= 2;
    EDR_type %= 2;
    if(EDR_type == 1)
    {
        if(signal_num == 1)
            return &EDRsignal_RPeaks_one;
        else
            return &EDRsignal_RPeaks_two;
    }
    else
        return &EDRsignal_Waves;
}

std::vector<double>* sig_edr::retrieveEDR_StdVec(int EDR_type, int signal_num
                                                 )
{
    signal_num %= 2;
    EDR_type %= 2;
    if(EDR_type == 1)
    {
        if(signal_num == 1)
            EDRsignal = EDRsignal_RPeaks_one.toStdVector();
        else
            EDRsignal = EDRsignal_RPeaks_two.toStdVector();
    }
    else
        EDRsignal = EDRsignal_Waves.toStdVector();

    return &EDRsignal;
}

double sig_edr::integral(QVector<double> &value
                         )
{
    int count   =   value.size();
    double sum  =   0;

    while (!value.isEmpty())
    {
      sum   +=  value.first();
      value.erase(value.begin());
    }

    sum /= count;

    return sum;
}

void sig_edr::calculate_signal_from_QRS(const QVector<double> &QRSIntegrals_one,
                                        const QVector<double> &QRSIntegrals_two
                                        )
{
    QVector<double>::const_iterator iterator_one;
    QVector<double>::const_iterator iterator_two;

    EDRsignal_Waves.clear();

    iterator_two = QRSIntegrals_two.begin();

    for(iterator_one = QRSIntegrals_one.begin(); iterator_one != QRSIntegrals_one.end(); iterator_one++)
    {
        EDRsignal_Waves << atan(*iterator_one / *iterator_two);
        iterator_two++;
    }
}
