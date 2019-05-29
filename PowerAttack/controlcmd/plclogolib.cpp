#include "plclogolib.h"

Plclogolib::Plclogolib()
{
    logoerror = 0;
    // DEFAULT PARAM
    logo_mpi = 1 ;
    logo_rack = 1;
    logo_slot = 0;

}

Plclogolib::~Plclogolib()
{


}


/**
 * @brief Plclogolib::setLogoCon
 *\n
 * Setting ip addres and establishes the connection to the network
 *
 * @param ip IP address of the Logo or router
 * @param port number of the Logo or router (default 102)
 * @return  1 = error , 0 = ok
 */

int Plclogolib::setLogoCon(QString ip , int port)
{
    int error = 0;
    error = this->setTcp(ip,port);

    if (error == 0){
        this->ok_con = this->setPlc("logo",logo_mpi,logo_rack,logo_slot);
    }
    return this->ok_con; // 1 = OK

}



// Read data Logo

/**
 * @brief Plclogolib::getLogoValue
 *\n
 * Read a 16-bit integer on area VW
 *\n
 * @param area numword address of the data
 * \n
 * example : numword = 952 to 982(AM1 to AM16)
 * or see Logo Address Table
 * \n
 * @return returns the value read
 */

int Plclogolib::getLogoValue(int numword)
{
    int word = 0;
    logoerror = daveReadBytes(dc,daveDB,0,numword,WORD,NULL);
    if (logoerror == 0){
        word=daveGetU16(dc);
    }
    return word;
}


/**
 * @brief Plclogolib::getLogoAnalogIn
 * \n
 * @param num_anag number of analog input
 * \n example (1 = AI1 , 2 = AI2 ecc. ecc
 * @return returns the value read
 */

int Plclogolib::getLogoAnalogIn(int num_anag_input)
{
    QList <int> list;
    int val = 0;
    int areastart = 926;

    if (num_anag_input == 0){
        num_anag_input = 1;
    }
    if (num_anag_input == 9){
        num_anag_input = 8;
    }

    num_anag_input = num_anag_input-1;

    for (int i = 0 ; i<8 ; i++){
        logoerror = daveReadBytes(dc,daveDB,0,areastart,WORD,NULL);
        if (logoerror == 0){
            val =daveGetU16(dc);
        }
        list.append(val);
        areastart = areastart +2;
     }
    return list.at(num_anag_input);

}



/**
 * @brief Plclogolib::getLogoAnalogMerker
 * \n
 * @param num_anag number of analog merker
 * \n example (1 = AM1 , 2 = AM2 ecc. ecc
 * @return returns the value read
 */

int Plclogolib::getLogoAnalogMerker(int num_anag_merker)
{
    QList <int> list;
    int val = 0;
    int areastart = 952;

    if (num_anag_merker == 0){
        num_anag_merker = 1;
    }
    if (num_anag_merker == 17){
        num_anag_merker = 16;
    }

    num_anag_merker = num_anag_merker-1;

    for (int i = 0 ; i<16 ; i++){
        logoerror = daveReadBytes(dc,daveDB,0,areastart,WORD,NULL);
        if (logoerror == 0){
            val =daveGetU16(dc);
        }
        list.append(val);
        areastart = areastart +2;
     }
    return list.at(num_anag_merker);

}


/**
 * @brief Plclogolib::getLogoAnalogOut
 * \n
 * @param num_anag number of analog out
 * \n example (1 = AQ1 , 2 = AQ2
 * @return returns the value read
 */

int Plclogolib::getLogoAnalogOut(int num_anag_out)
{
    QList <int> list;
    int val = 0;
    int areastart = 944;

    if (num_anag_out == 0){
        num_anag_out = 1;
    }
    if (num_anag_out == 3){
        num_anag_out = 2;
    }

    num_anag_out = num_anag_out-1;

    for (int i = 0 ; i<2 ; i++){
        logoerror = daveReadBytes(dc,daveDB,0,areastart,WORD,NULL);
        if (logoerror == 0){
            val =daveGetU16(dc);
        }
        list.append(val);
        areastart = areastart +2;
     }
    return list.at(num_anag_out);

}


/**
 * @brief Plclogolib::getLogoBitArray
 *\n
 * Reads the individual bits from one area VW (max 16 bit)
 * see Logo Address Table
 * \n
 * @param areastart start address of the data
 *\n
 * @param arealen number of bits
 *\n
 * @return returns the value read in an array of bits
 */

QBitArray Plclogolib::getLogoBitArray(int areastart, int arealen)
{
    int bytea,byteb,bit16;
    int dbbit = 0;
    QBitArray  qba;

    logoerror = daveReadBytes(dc,daveDB,0,areastart,WORD,NULL);
    if (logoerror == 0){
        bit16 = daveGetU16(dc);
        bytea = bit16 >> 8;
        byteb = bit16 << 8;
        dbbit = byteb|bytea;
        }
    qba = intToBitArray(dbbit,arealen);
    return qba;
}


/**
 * @brief Plclogolib::getLogoBit
 *\n
 * Read the individual bits of an area "V"
 *\n
 * @param num_bit Number of byte
 * @param num_byte Number of bit
 * \n
 * Num byte = 942(Q1 to Q8)
 * = 943(Q9 to Q16)
 * = 948(M1 to M8)
 * = 949(M9 to M16)
 * = 950(M17 to M24)
 * = 951(M25 to M27)
 *\n
 * @return returns the bool value read
 */

bool Plclogolib::getLogoBit(int num_byte, int num_bit)
{
    QBitArray bit;
    bool pos = false;

    if (num_bit > 8){
        num_bit = 8;
    }
    bit = this->getLogoBitArray(num_byte,8);
    pos = bit.at(num_bit);
    return pos;

}



// Write data logo

/**
 * @brief Plclogolib::setLogoValue
 *\n
 * Writes a 16-bit integer on area VW
 *\n
 * @param area num address of the data
 * \n
 * num area = 952 to 982(AM1 to AM16)
 * or see Logo Address Table
 * no AQ area
 * \n
 * @param num dato to write
 */

void Plclogolib::setLogoValue(int numword ,int num)
{

    int buf_int = daveSwapIed_16((int)num);
    logoerror = daveWriteBytes(dc,daveDB,0,numword,WORD,&buf_int);

}


/**
 * @brief Plcqtlib::setLogoByte
 *\n
 * Writes a byte of a VW area
 **\n
 * @param area num address of the data
 * \n
 * see Logo Address Table (no AQ area)
 * \n
 * @param num dato to write
 */

void Plclogolib::setLogoByte(int area,int num)
{
    buf_byte = (int)num;
    error =  daveWriteBytes(dc,daveDB,0,area,BYTE,&buf_byte);

}



/**
 * @brief Plclogolib::setLogoBit
 *\n
 * Writes the individual bits of an area of a data block
 *\n
 * @param area num address of the data
 *\n
 * @param byte_adr number byte address
 * \n
 * number byte address = 942(Q1 to Q8)
 * = 943(Q9 to Q16)
 * = 948(M1 to M8)
 * = 949(M9 to M16)
 * = 950(M17 to M24)
 * = 951(M25 to M27)
 * = Area V (all)
 * @param  bit_adr address of the bit to be set
 * bit 0 = Q1 ; bit 1 = Q2 ; ecc....
 */

void Plclogolib::setLogoBit(int byte_adr ,int num_bit)
{

    logoerror = daveSetBit(dc,daveDB ,0,byte_adr,num_bit);

}



/**
 * @brief Plclogolib::resetLogoBit
 *\n
 * Reset the individual bits from one area of a data block
 *\n
 * @param area area data
 *\n
 * @param byte_adr number byte address
 * \n
 * number byte address = 942(Q1 to Q8)
 * = 943(Q9 to Q16)
 * = 948(M1 to M8)
 * = 949(M9 to M16)
 * = 950(M17 to M24)
 * = 951(M25 to M27)
 * = Area V (all)
 * @param  bit_adr address of the bit to be set
 * bit 0 = Q1 ; bit 1 = Q2 ; ecc....
 */

void Plclogolib::resetLogoBit(int byte_adr , int num_bit)
{

    logoerror = daveClrBit(dc,daveDB ,0,byte_adr,num_bit);

}



/**
 * @brief Plcqtlib::getError
 *\n
 * Detects the general error message
 *\n
 * @return returns the error message
 * @brief mess = "ok" no error
 */
QString Plclogolib::getLogoError() const
{
    char *er;
    er = daveStrerror(logoerror);
    QString mess(er);
    return mess;
}
































