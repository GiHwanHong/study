#pragma once

#include <QString>
#include <QStringList>

class WTempDir;

// zip ������ ���������Ѵ���, �Ҹ�� �ٽ� ������.
// ZIP���ϳ��� ������ ����/�����ϱ����� helper class.
class WZipFileDelegate
{
public:
	// zipPath�� ���������� temp dir �� ����������.
    WZipFileDelegate(const QString& zipPath = QString());
	// m_autoCompressBack�� true(�⺻�� false)�� ��ü�Ҹ�� 
    virtual ~WZipFileDelegate();
	// zip���ϳ��� ����� relPathInZip ������ ������ Ǯ�� ���·�
	// �����ϴ� local file path�� ��ȯ. �������� ������, null
	// QString() ��ȯ
	QString localPath(const QString& relPathInZip) const;
	// ���������� ������ �ٽ� ���� zipPath�� ������.
	bool compressBack();
	// ���۰��ɻ���Ȯ��
	bool isValid() const;

	void setAutoCompressBack(bool enabled);
	bool autoCompressBack() const {
		return m_autoCompressBack;
	}
	void setCreateBackupWhenCompressBack(bool enabled) {
		m_createBackupWhenCompressBack = enabled;
	}
private:
	// ������ �ڵ����� ���� zip�� local file�� ����?
	bool m_autoCompressBack;
	bool m_createBackupWhenCompressBack;
	QString m_zipPath;
	WTempDir* m_tempDir;
	QStringList m_extractedFileList;
};




