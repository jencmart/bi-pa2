#ifndef __PROGTEST__

#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include <set>
#include <queue>
#include <memory>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <fstream>


using namespace std;
const unsigned int ENDIAN_LITTLE = 0x4949;
const unsigned int ENDIAN_BIG = 0x4d4d;
#endif /* __PROGTEST__ */

inline uint16_t LE_encode16bit(char lo, char hi) {
    return (uint16_t) ((((unsigned char) hi) << 8) | ((unsigned char) lo));
}

inline uint16_t BE_encode16bit(char lo, char hi) {
    return (uint16_t) ((((unsigned char) lo) << 8) | ((unsigned char) hi));
}

inline uint16_t get4MostSignif(char byte) { return (uint16_t) (((unsigned char) byte) >> 4); }

inline uint16_t get4LeastSignif(char byte) { return (uint16_t) (((unsigned char) byte) & 0x0F); }

inline char get8_MostSignifFrom_uint16(uint16_t num) { return (unsigned char) (num >> 8); }

inline char get8_LeastSignifFrom_uint16(uint16_t num) { return (unsigned char) (num & 0xFF); }

class Image {
private:
    struct Pixel {
    private:
        uint16_t channels[15];
    public:
        void setChannel(int i, uint16_t value) {
            channels[i] = value;
        }

        uint16_t getChannel(int i) {
            return channels[i];
        }
    };

    uint16_t m_width;
    uint16_t m_height;
    uint16_t m_noChannels;
    uint16_t m_noBits;
    string m_srcFileName;
    int m_angle;
    uint16_t m_inputEndian;
    uint16_t m_height_new;
    uint16_t m_width_new;
    vector<vector<Pixel>> m_data;
    vector<vector<Pixel>> m_data_new;

    int setAngle(int angle) {
        angle = (angle - 360 * (angle / 360)) / 90;

        if (angle == 1 || angle == -3)
            return 1;
        else if (angle == 2 || angle == -2)
            return 2;
        else if (angle == 3 || angle == -1)
            return 3;
        else
            return 0;
    }

    uint16_t setHeightNew() {
        if (m_angle == 1 || m_angle == 3)
            return m_width;
        return m_height;
    }

    uint16_t setWidthNew() {
        if (m_angle == 1 || m_angle == 3)
            return m_height;
        return m_width;
    }

public:
    Image(uint16_t width, uint16_t height, uint16_t noChannels, uint16_t noBits, const string &srcFileName, int angle,
          uint16_t endian) :
            m_width(width),
            m_height(height),
            m_noChannels(noChannels),
            m_noBits(noBits),
            m_srcFileName(srcFileName),
            m_angle(setAngle(angle)),
            m_inputEndian(endian),

            m_height_new(setHeightNew()),
            m_width_new(setWidthNew()),
            m_data(m_height, vector<Pixel>(m_width)),
            m_data_new(m_height_new, vector<Pixel>(m_width_new)) {};

    static bool evaluateAngle(int angle) { return angle % 90 == 0; }

    void setPixVal(int i, int j, int channel, uint16_t value) { m_data[i][j].setChannel(channel, value); }

    void setPixValNew(int i, int j, int channel, uint16_t value) { m_data_new[i][j].setChannel(channel, value); }

    uint16_t getPixValNew(int i, int j, int channel) { return m_data_new[i][j].getChannel(channel); }

    int getWSquares() { return !(m_width % 8) ? m_width / 8 : m_width / 8 + 1; }

    int getHSquares() { return !(m_height % 8) ? m_height / 8 : m_height / 8 + 1; }

    int getWSquaresNew() { return !(m_width_new % 8) ? m_width_new / 8 : m_width_new / 8 + 1; }

    int getHSquaresNew() { return !(m_height_new % 8) ? m_height_new / 8 : m_height_new / 8 + 1; }

    uint16_t getWidth() { return m_width; }

    uint16_t getHeight() { return m_height; }

    uint16_t getInputEndian() { return m_inputEndian; }

    uint16_t getHeightNew() { return m_height_new; }

    uint16_t getWidthNew() { return m_width_new; }

    uint16_t getBits() { return m_noBits; }

    uint16_t getChannles() { return m_noChannels; }

    int getAngle() { return m_angle; }
};

void
getRotatedCoords(Image &img, int realPixelRow, int realPixelCol, int &realPixelRowRotated, int &realPixelColRotated,
                 int angle) {
    if (angle == 0) {
        realPixelRowRotated = realPixelRow;
        realPixelColRotated = realPixelCol;
    } else if (angle == 1) {
        realPixelRowRotated = realPixelCol;
        realPixelColRotated = img.getHeight() - 1 - realPixelRow; // -1 protze od nuly...
    } else if (angle == 2) {
        realPixelRowRotated = img.getHeight() - 1 - realPixelRow;
        realPixelColRotated = img.getWidth() - 1 - realPixelCol;
    } else if (angle == 3) {
        realPixelRowRotated = img.getWidth() - 1 - realPixelCol;
        realPixelColRotated = realPixelRow;
    }
    return;
}

bool loadValue(ifstream &f, uint16_t endian, uint16_t bits, uint16_t &value) {
    char lo, hi;
    static int counter;
    static char loByt;

    if (bits == 0) { // 1 bit data
        if (counter == 0 || counter == 8) {
            counter = 0;
            f.get(loByt);
            if (f.bad() || f.eof()) {
                f.clear();
                counter = 0;
                return false;
            }
        }
        value = (uint16_t) ((((unsigned char) loByt) >> counter) & 1);
        counter++;
        return true;
    } else if (bits == 2) { // 4bit
        if (counter == 0 || counter == 8) {
            counter = 0;
            f.get(loByt);
            if (f.bad() || f.eof()) {
                f.clear();
                counter = 0;
                return false;
            }
        }
        value = (uint16_t) ((((unsigned char) loByt) >> counter) & 0x0F);
        counter += 4;
        return true;
    } else if (bits == 3) { // 8 bit data
        f.get(lo);
        if (f.bad() || f.eof()) {
            f.clear();
            return false;
        }
        value = (uint16_t) (unsigned char) lo;
    } else if (bits == 4) { // 16 bit data
        f.get(lo).get(hi);
        if (f.bad() || f.eof()) {
            f.clear();
            return false;
        }
        value = (endian == ENDIAN_LITTLE) ? LE_encode16bit(lo, hi) : BE_encode16bit(lo, hi);
    }

    return true;
}

bool loadOnePixel(Image &img, ifstream &f, int hSquare, int wSquare, int i, int j, int channel) {
    int realPixelRow = hSquare * 8 + i;
    int realPixelColumn = wSquare * 8 + j;
    int realPixRowRotated;
    int realPixColRotated;
    uint16_t value;

    if (!loadValue(f, img.getInputEndian(), img.getBits(), value))
        return false;
    getRotatedCoords(img, realPixelRow, realPixelColumn, realPixRowRotated, realPixColRotated, img.getAngle());
    if (realPixelRow >= img.getHeight() || realPixelColumn >= img.getWidth())
        return value == 0; // borers must be 00
    img.setPixVal(realPixelRow, realPixelColumn, channel, value);
    img.setPixValNew(realPixRowRotated, realPixColRotated, channel, value);

    return true;
}

bool loadBlock_8(Image &img, ifstream &f, int hSquare, int wSquare, int channel) {
    for (int jtmp = 0; jtmp < 8; jtmp++)
        for (int i = 0; i <= jtmp; i++)
            if (!loadOnePixel(img, f, hSquare, wSquare, i, jtmp - i, channel))
                return false;
    for (int itmp = 1; itmp < 8; itmp++)
        for (int j = 7; j >= itmp; j--)
            if (!loadOnePixel(img, f, hSquare, wSquare, itmp + 7 - j, j, channel))
                return false;

    return true;
}

bool loadImageData(ifstream &f, Image *img) {
    for (int hSquare = 0; hSquare < img->getHSquares(); hSquare++)
        for (int wSquare = 0; wSquare < img->getWSquares(); wSquare++)
            for (int channel = 0; channel < img->getChannles(); channel++) {
                if (!loadBlock_8(*img, f, hSquare, wSquare, channel))
                    return false;
            }

    return true;
}

Image *loadImageHeader(ifstream &f, const string &srcFileName, int angle) {
    char endianLo, endianHi, widthLo, widthHi, heightLo, heightHi, formatLo, formatHi;
    uint16_t width, height, noBits, noChannels;
    uint16_t endian;

    f.get(endianLo).get(endianHi).get(widthLo).get(widthHi).get(heightLo).get(heightHi).get(formatLo).get(formatHi);
    if (f.bad() || f.eof()) {
        f.clear();
        return NULL;
    }

    endian = LE_encode16bit(endianLo, endianHi);
    width = endian == ENDIAN_LITTLE ? LE_encode16bit(widthLo, widthHi) : BE_encode16bit(widthLo, widthHi);
    height = endian == ENDIAN_LITTLE ? LE_encode16bit(heightLo, heightHi) : BE_encode16bit(heightLo, heightHi);
    noBits = endian == ENDIAN_LITTLE ? get4MostSignif(formatLo) : get4MostSignif(formatHi);
    noChannels = endian == ENDIAN_LITTLE ? get4LeastSignif(formatLo) : get4LeastSignif(formatHi);

    if ((endian == ENDIAN_LITTLE) &&
        (!width || !height || !noChannels || formatHi || (noBits != 0 && noBits != 2 && noBits != 3 && noBits != 4)))
        return NULL;
    if ((endian == ENDIAN_BIG) &&
        (!width || !height || !noChannels || formatLo || (noBits != 0 && noBits != 2 && noBits != 3 && noBits != 4)))
        return NULL;
    if (endian != ENDIAN_BIG && endian != ENDIAN_LITTLE)
        return NULL;

    return new Image(width, height, noChannels, noBits, srcFileName, angle, endian);
}

Image *loadImage(const string &srcFileName, int angle) {
    ifstream f(srcFileName, ios::binary | ios::in);
    Image *img;
    char a;

    if (!(img = loadImageHeader(f, srcFileName, angle))) {
        f.close();
        return NULL;
    }

    if (!loadImageData(f, img)) {
        f.close();
        return NULL;
    }
    f.get(a);
    if (!f.eof()) {
        f.close();
        return NULL;
    }
    f.close();
    return img;
}

bool
writeOnePixel(Image &img, ofstream &f, int hSquare, int wSquare, int i, int j, int channel, unsigned int byteOrder) {
    int realRow = hSquare * 8 + i;
    int realCol = wSquare * 8 + j;
    static char writeVal;
    static int counter;

    if (img.getBits() == 0) { // zapisovani 1bit hodnot;
        if (realRow >= img.getHeightNew() || realCol >= img.getWidthNew());
        else
            writeVal |= (char) img.getPixValNew(realRow, realCol, channel) << counter;

        if (++counter == 8) {
            f.put(writeVal);
            writeVal &= 0x00;
            counter = 0;
            if (f.bad() || f.eof() || f.fail()) {
                f.clear();
                return false;
            }
        }
        return true;
    } else if (img.getBits() == 2) {
        if (realRow >= img.getHeightNew() || realCol >= img.getWidthNew());
        else
            writeVal |= (char) img.getPixValNew(realRow, realCol, channel) << counter;

        counter += 4;
        if (counter == 8) {
            f.put(writeVal);
            writeVal &= 0x00;
            counter = 0;
            if (f.bad() || f.eof() || f.fail()) {
                f.clear();
                return false;
            }
        }
        return true;
    } else if (img.getBits() == 3) {                                            // 8 bit
        if (realRow >= img.getHeightNew() || realCol >= img.getWidthNew())
            f.put('\0');
        else
            f.put((char) img.getPixValNew(realRow, realCol, channel));

        if (f.bad() || f.eof() || f.fail()) {
            f.clear();
            return false;
        }
        return true;
    } else {                                                                    // 16 bit
        if (realRow >= img.getHeightNew() || realCol >= img.getWidthNew())
            f.put('\0').put('\0');
        else {
            if (byteOrder == ENDIAN_LITTLE) {
                f.put(get8_LeastSignifFrom_uint16(img.getPixValNew(realRow, realCol, channel)));
                f.put(get8_MostSignifFrom_uint16(img.getPixValNew(realRow, realCol, channel)));
            } else {
                f.put(get8_MostSignifFrom_uint16(img.getPixValNew(realRow, realCol, channel)));
                f.put(get8_LeastSignifFrom_uint16(img.getPixValNew(realRow, realCol, channel)));
            }
        }
        if (f.bad() || f.eof() || f.fail()) {
            f.clear();
            return false;
        }
        return true;
    }
}

bool writeBlock_8(Image &img, ofstream &f, int hSquare, int wSquare, int channel, unsigned int byteOrder) {
    for (int jtmp = 0; jtmp < 8; jtmp++)
        for (int i = 0; i <= jtmp; i++)
            if (!writeOnePixel(img, f, hSquare, wSquare, i, jtmp - i, channel, byteOrder))
                return false;
    for (int itmp = 1; itmp < 8; itmp++)
        for (int j = 7; j >= itmp; j--)
            if (!writeOnePixel(img, f, hSquare, wSquare, itmp + 7 - j, j, channel, byteOrder))
                return false;

    return true;
}

bool writeData(Image &img, ofstream &f, unsigned int byteOrder) {
    for (int hSquare = 0; hSquare < img.getHSquaresNew(); hSquare++)
        for (int wSquare = 0; wSquare < img.getWSquaresNew(); wSquare++)
            for (int channel = 0; channel < img.getChannles(); channel++)
                if (!writeBlock_8(img, f, hSquare, wSquare, channel, byteOrder))
                    return false;

    return true;
}

bool writeHeader(Image &img, ofstream &f, uint16_t byteOrder) {
    byteOrder == ENDIAN_LITTLE ? f.put(get8_LeastSignifFrom_uint16(byteOrder)) : f.put(
            get8_MostSignifFrom_uint16(byteOrder));
    byteOrder == ENDIAN_LITTLE ? f.put(get8_MostSignifFrom_uint16(byteOrder)) : f.put(
            get8_LeastSignifFrom_uint16(byteOrder));
    byteOrder == ENDIAN_LITTLE ? f.put(get8_LeastSignifFrom_uint16(img.getWidthNew())) : f.put(
            get8_MostSignifFrom_uint16(img.getWidthNew()));
    byteOrder == ENDIAN_LITTLE ? f.put(get8_MostSignifFrom_uint16(img.getWidthNew())) : f.put(
            get8_LeastSignifFrom_uint16(img.getWidthNew()));
    byteOrder == ENDIAN_LITTLE ? f.put(get8_LeastSignifFrom_uint16(img.getHeightNew())) : f.put(
            get8_MostSignifFrom_uint16(img.getHeightNew()));
    byteOrder == ENDIAN_LITTLE ? f.put(get8_MostSignifFrom_uint16(img.getHeightNew())) : f.put(
            get8_LeastSignifFrom_uint16(img.getHeightNew()));
    byteOrder == ENDIAN_LITTLE ? f.put((unsigned char) ((img.getChannles() & 0x0F) | ((img.getBits() & 0x0F) << 4)))
                               : f.put('\0');
    byteOrder == ENDIAN_LITTLE ? f.put('\0') : f.put(
            (unsigned char) ((img.getChannles() & 0x0F) | ((img.getBits() & 0x0F) << 4)));
    return !(f.bad() || f.eof());
}

bool writeImage(Image &img, const string dstFileName, uint16_t byteOrder) {
    ofstream f(dstFileName, ios::binary | ios::out);

    if (!writeHeader(img, f, byteOrder)) {
        f.flush();
        f.close();
        return false;
    }

    if (!writeData(img, f, byteOrder)) {
        f.flush();
        f.close();
        return false;
    }
    f.flush();
    f.close();
    return true;
}

bool rotateImage(const char *srcFileName, const char *dstFileName, int angle, unsigned int byteOrder) {
    Image *img;

    if (!Image::evaluateAngle(angle))
        return false;

    if ((img = loadImage((string) srcFileName, angle)) == NULL)
        return false;

    return writeImage(*img, dstFileName, (uint16_t) byteOrder);

}

#ifndef __PROGTEST__

bool identicalFiles(const char *fileName1, const char *fileName2) {
    ifstream f(fileName1, ios::binary | ios::in);
    ifstream j(fileName2, ios::binary | ios::in);
    char s1, s2;

    while (true) {
        f.get(s1);
        j.get(s2);

        if (f.eof() || j.eof())
            break;

        if (s1 == s2)
            continue;
        else
            throw "SOUBORY NEJSOU STEJNE\n";
    }

    if (f.eof() && j.eof()) {
        cout << "SOUBOR JE SHODNY S REFERENCNIM SOUBOREM" << endl;
        return true;
    }

    return false;
}


void basicTest() {
    assert (rotateImage("../testFiles/input_00.img", "../testFiles//testOutput/output_00.img", 0, ENDIAN_LITTLE)
            && identicalFiles("../testFiles//testOutput/output_00.img", "../testFiles/ref_00.img"));
    assert (rotateImage("../testFiles/input_01.img", "../testFiles//testOutput/output_01.img", 90, ENDIAN_LITTLE)
            && identicalFiles("../testFiles//testOutput/output_01.img", "../testFiles/ref_01.img"));
    assert (rotateImage("../testFiles/input_02.img", "../testFiles//testOutput/output_02.img", 540, ENDIAN_LITTLE)
            && identicalFiles("../testFiles//testOutput/output_02.img", "../testFiles/ref_02.img"));
    assert (rotateImage("../testFiles/input_03.img", "../testFiles//testOutput/output_03.img", -900450, ENDIAN_LITTLE)
            && identicalFiles("../testFiles//testOutput/output_03.img", "../testFiles/ref_03.img"));
    assert (rotateImage("../testFiles/input_04.img", "../testFiles//testOutput/output_04.img", 90, ENDIAN_LITTLE)
            && identicalFiles("../testFiles//testOutput/output_04.img", "../testFiles/ref_04.img"));
    assert (rotateImage("../testFiles/input_05.img", "../testFiles//testOutput/output_05.img", 270, ENDIAN_LITTLE)
            && identicalFiles("../testFiles//testOutput/output_05.img", "../testFiles/ref_05.img"));
    assert (rotateImage("../testFiles/input_06.img", "../testFiles//testOutput/output_06.img", 90, ENDIAN_LITTLE)
            && identicalFiles("../testFiles//testOutput/output_06.img", "../testFiles/ref_06.img"));
    assert (rotateImage("../testFiles/input_07.img", "../testFiles//testOutput/output_07.img", 270, ENDIAN_LITTLE)
            && identicalFiles("../testFiles//testOutput/output_07.img", "../testFiles/ref_07.img"));
    assert (!rotateImage("../testFiles/input_08.img", "../testFiles//testOutput/output_08.img", 270, ENDIAN_LITTLE));
    assert (!rotateImage("../testFiles/input_09.img", "../testFiles//testOutput/output_09.img", -275, ENDIAN_LITTLE));
}

void extraTest() {
    // extra inputs (optional & bonus tests)
    assert (rotateImage("../testFiles/extra_input_00.img", "extra_out_00.img", 90, ENDIAN_LITTLE)
            && identicalFiles("extra_out_00.img", "../testFiles/extra_ref_00.img"));

    assert (rotateImage("../testFiles/extra_input_01.img", "extra_out_01.img", 90, ENDIAN_BIG)
            && identicalFiles("extra_out_01.img", "../testFiles/extra_ref_01.img"));

    assert (rotateImage("../testFiles/extra_input_02.img", "extra_out_02.img", 180, ENDIAN_BIG)
            && identicalFiles("extra_out_02.img", "../testFiles/extra_ref_02.img"));

    assert (rotateImage("../testFiles/extra_input_03.img", "extra_out_03.img", 270, ENDIAN_LITTLE)
            && identicalFiles("extra_out_03.img", "../testFiles/extra_ref_03.img"));

    assert (rotateImage("../testFiles/extra_input_04.img", "extra_out_04.img", 90, ENDIAN_LITTLE)
            && identicalFiles("extra_out_04.img", "../testFiles/extra_ref_04.img"));
    assert (rotateImage("../testFiles/extra_input_05.img", "extra_out_05.img", 270, ENDIAN_LITTLE)
            && identicalFiles("extra_out_05.img", "../testFiles/extra_ref_05.img"));
    assert (rotateImage("../testFiles/extra_input_06.img", "extra_out_06.img", 180, ENDIAN_BIG)
            && identicalFiles("extra_out_06.img", "../testFiles/extra_ref_06.img"));
    assert (rotateImage("../testFiles/extra_input_07.img", "extra_out_07.img", 0, ENDIAN_BIG)
            && identicalFiles("extra_out_07.img", "../testFiles/extra_ref_07.img"));
    assert (rotateImage("../testFiles/extra_input_08.img", "extra_out_08.img", 90, ENDIAN_LITTLE)
            && identicalFiles("extra_out_08.img", "../testFiles/extra_ref_08.img"));
    assert (rotateImage("../testFiles/extra_input_09.img", "extra_out_09.img", 270, ENDIAN_LITTLE)
            && identicalFiles("extra_out_09.img", "../testFiles/extra_ref_09.img"));
    assert (rotateImage("../testFiles/extra_input_10.img", "extra_out_10.img", 180, ENDIAN_BIG)
            && identicalFiles("extra_out_10.img", "../testFiles/extra_ref_10.img"));
    assert (rotateImage("../testFiles/extra_input_11.img", "extra_out_11.img", 0, ENDIAN_BIG)
            && identicalFiles("extra_out_11.img", "../testFiles/extra_ref_11.img"));
}

int main(void) {
    basicTest();
    extraTest();
    return 0;
}

#endif /* __PROGTEST__ */

