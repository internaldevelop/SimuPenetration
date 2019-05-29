#ifndef PLCLOGOLIB_H
#define PLCLOGOLIB_H

#include <QObject>
#include <QBitArray>
#include "plcqtlib.h"
#include "plcqtlib_global.h"
#include "nodave.h"

class PLCQTLIBSHARED_EXPORT Plclogolib : public Plcqtlib
{


public:
    Plclogolib();
    ~Plclogolib();
    int setLogoCon(QString ip, int port);
    QString  getLogoError()const;

    //Read data
    int getLogoValue(int address);
    int getLogoAnalogIn(int num_anag_input);
    int getLogoAnalogMerker(int num_anag_merker);
    int getLogoAnalogOut(int num_anag_out);
    bool getLogoBit(int num_byte, int num_bit);
    QBitArray getLogoBitArray(int areastart, int arealen);

    //Write data
    void setLogoByte(int area,int num);
    void setLogoValue(int numword , int num);
    void setLogoBit(int byte_adr , int num_bit);
    void resetLogoBit(int byte_adr , int num_bit);


private:
    int logoerror;
    int logo_mpi;int logo_rack;int logo_slot;

};

#endif // PLCLOGOLIB_H
