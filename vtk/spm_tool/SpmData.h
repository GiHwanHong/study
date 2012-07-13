#if !defined(AFX_SPMDATA_H__161298A6_8F2C_4D9B_85E4_F7E6FE502073__INCLUDED_)
#define AFX_SPMDATA_H__161298A6_8F2C_4D9B_85E4_F7E6FE502073__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <QScopedArrayPointer>
#include <QLatin1String>
#include <QString>
#include <QList>

class QFile;

//3���� �������� ȭ���� Ư�� ������
enum {
	GOOD_PXL = 0x01,			//good pixel
	NOISE_PXL = 0x02,			//noise pixel. do not display
	RESTORE_PXL = 0x04,			//Zoom ����� �� �� ä������ pixel
	RECONS_PXL = 0x08,			//NOISE_PXL �� ������ ������ ���Ͽ� �����Ǵ� PXL
	INTERMEDIATE_PXL = 0x10,
	IN_TILE_PXL = 0x20,			//unwrapping�� ����ϴ� ����
	FIXED_NOISE = 0x40,			//unwrapping�� ����ϴ� ����
	WRAP_PXL = 0x80,			//wrapping pixel in WSI
	NEIGHBOR_PXL = 0x100,		//Bump�� �ֺ��� �ִ� �ȼ�. **** ���� ������.
};

// Bond Finger Direct (Using Presolder Algorithm...)
enum {
	BF_DIRECT_X = 0, 	// Bond Finger�� ���η� �� ����϶�
	BF_DIRECT_Y = 1, 	// Bond Finger�� ���η� �� ����϶�
};

class CSpmData
{
public:
	CSpmData();
	virtual ~CSpmData();
public:
	void resize(int nRate);
	void stitch(int nRow, int nCol, const QString& strSpmFile);
	void prepareStitching(const QString& strLeftTopFile,
						  const QString& strRightBottomFile);
	void copyRoi(CSpmData &SpmSrc, int nX1, int nY1, int nX2, int nY2);
	void copy(CSpmData &SpmSrc);
	void saveToFile(const QString& strFilename);
	bool loadFromFile(QString strFilename);
	QByteArray byteData(const QLatin1String& strType, float fThreshold);
	int dataCount() const {
		return nSXNum * nSYNum;
	}
	int countX() const {
		return nSXNum;
	}
	int countY() const {
		return nSYNum;
	}
	QList<float> minMax(void);// [0]:min, [1]:max
	float heightAt(int x, int y);
protected:
	qint16 wdVersion;
	QString strTitle;
	QString strDate;
	QString strObj;
	QString strInsp;
	quint8 nMethod;
	quint8 nProcessing;
	int nSXNum;
	int nSYNum;
	int nPixelBinning;
	float fXresol;
	float fYresol;
	float fXcen;
	float fYcen;
	float fHMax;
	float fHMin;
	QScopedArrayPointer<quint8> surfaceValidity;
	QScopedArrayPointer<float> surfaceHeight;

	void prepareData();
	void clearData();
	bool writeStr(QFile &f, const QString& str);
	bool readStr(QFile &f, QString& str);
};

#endif // !defined(AFX_SPMDATA_H__161298A6_8F2C_4D9B_85E4_F7E6FE502073__INCLUDED_)
