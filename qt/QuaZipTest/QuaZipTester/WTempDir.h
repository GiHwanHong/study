#pragma once

#include <QDir>

class WTempDir
{
public:
	// �ӽõ��丮�� QTemporaryFile�� ����� ����
	WTempDir(QString dirNameTemplatePrefix = QString());
	// �ӽõ��丮�� ������.
	virtual ~WTempDir();
	// ��ȯ�� QDir�� WTempDir()��ü�� �ı��� ���Ŀ� ����� ��� ����
	// �߻���.
	QDir& dir() {
		return m_dir;
	}
	bool isValid() const {
		return !m_tempDirPath.isNull();
	}
protected:
	QString m_tempDirPath;
	QDir m_dir;
};
