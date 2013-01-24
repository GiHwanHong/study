static bool extract(const QString & filePath, const QString & extDirPath, const QString & singleFileName = QString(""))
{
	QuaZip zip(filePath);
	if (!zip.open(QuaZip::mdUnzip)) {
		qWarning("testRead(): zip.open(): %d", zip.getZipError());
		return false;
	}
	zip.setFileNameCodec("IBM866");
	qWarning("%d entries\n", zip.getEntriesCount());
	qWarning("Global comment: %s\n", zip.getComment().toLocal8Bit().constData());
	QuaZipFileInfo info;
	QuaZipFile file(&zip);
	QFile out;
	QString name;
	char c;
	for (bool more = zip.goToFirstFile(); more; more = zip.goToNextFile()) {
		if (!zip.getCurrentFileInfo(&info)) {
			qWarning("testRead(): getCurrentFileInfo(): %d\n", zip.getZipError());
			return false;
		}
		if (!singleFileName.isEmpty())
			if (!info.name.contains(singleFileName))
				continue;
		if (!file.open(QIODevice::ReadOnly)) {
			qWarning("testRead(): file.open(): %d", file.getZipError());
			return false;
		}
		name = QString("%1/%2").arg(extDirPath).arg(file.getActualFileName());
		if (file.getZipError() != UNZ_OK) {
			qWarning("testRead(): file.getFileName(): %d", file.getZipError());
			return false;
		}
		//out.setFileName("out/" + name);
		out.setFileName(name);
		// this will fail if "name" contains subdirectories, but we don't mind that
		out.open(QIODevice::WriteOnly);
		// Slow like hell (on GNU/Linux at least), but it is not my fault.
		// Not ZIP/UNZIP package's fault either.
		// The slowest thing here is out.putChar(c).
		while (file.getChar(&c)) out.putChar(c);
		out.close();
		if (file.getZipError() != UNZ_OK) {
			qWarning("testRead(): file.getFileName(): %d", file.getZipError());
			return false;
		}
		if (!file.atEnd()) {
			qWarning("testRead(): read all but not EOF");
			return false;
		}
		file.close();
		if (file.getZipError() != UNZ_OK) {
			qWarning("testRead(): file.close(): %d", file.getZipError());
			return false;
		}
	}
	zip.close();
	if (zip.getZipError() != UNZ_OK) {
		qWarning("testRead(): zip.close(): %d", zip.getZipError());
		return false;
	}
	return true;
}

static bool archive(const QString & filePath, const QDir & dir, const QString & comment = QString(""))
{
	QuaZip zip(filePath);
	zip.setFileNameCodec("IBM866");
	if (!zip.open(QuaZip::mdCreate)) {
		myMessageOutput(true, QtDebugMsg, QString("testCreate(): zip.open(): %1").arg(zip.getZipError()));
		return false;
	}
	if (!dir.exists()) {
		myMessageOutput(true, QtDebugMsg, QString("dir.exists(%1)=FALSE").arg(dir.absolutePath()));
		return false;
	}
	QFile inFile;
	// ����ݬ��Ѭ֬� ���ڬ��� ��Ѭ۬ݬ�� �� ��Ѭ��� ��֬ܬ���ڬӬ߬�
	QStringList sl;
	recurseAddDir(dir, sl);
	// ����٬լѬ֬� �ެѬ��ڬ� ��������ڬ� �ڬ� QFileInfo ��Ҭ�֬ܬ���
	QFileInfoList files;
	foreach (QString fn, sl) files << QFileInfo(fn);
	QuaZipFile outFile(&zip);
	char c;
	foreach(QFileInfo fileInfo, files) {
		if (!fileInfo.isFile())
			continue;
		// ����ݬ� ��Ѭ۬� �� ���լլڬ�֬ܬ���ڬ�, ��� �լ�ҬѬӬݬ�֬� �ڬެ� ����� ���լլڬ�֬ܬ���ڬ� �� �ڬެ֬߬Ѭ� ��Ѭ۬ݬ��
		// �߬Ѭ��ڬެ֬�: fileInfo.filePath() = "D:\Work\Sources\SAGO\svn\sago\Release\tmp_DOCSWIN\Folder\123.opn"
		// ���Ԭլ� ����ݬ� ��լѬݬ֬߬ڬ� ��Ѭ��� �����ܬ� fileNameWithSubFolders �Ҭ�լ֬� ��ѬӬ֬� "Folder\123.opn" �� ��.��.
		QString fileNameWithRelativePath = fileInfo.filePath().remove(0, dir.absolutePath().length() + 1);
		inFile.setFileName(fileInfo.filePath());
		if (!inFile.open(QIODevice::ReadOnly)) {
			myMessageOutput(true, QtDebugMsg, QString("testCreate(): inFile.open(): %1").arg(inFile.errorString().toLocal8Bit().constData()));
			return false;
		}
		if (!outFile.open(QIODevice::WriteOnly, QuaZipNewInfo(fileNameWithRelativePath, fileInfo.filePath()))) {
			myMessageOutput(true, QtDebugMsg, QString("testCreate(): outFile.open(): %1").arg(outFile.getZipError()));
			return false;
		}
		while (inFile.getChar(&c) && outFile.putChar(c));
		if (outFile.getZipError() != UNZ_OK) {
			myMessageOutput(true, QtDebugMsg, QString("testCreate(): outFile.putChar(): %1").arg(outFile.getZipError()));
			return false;
		}
		outFile.close();
		if (outFile.getZipError() != UNZ_OK) {
			myMessageOutput(true, QtDebugMsg, QString("testCreate(): outFile.close(): %1").arg(outFile.getZipError()));
			return false;
		}
		inFile.close();
	}
	// + �ܬ�ެެ֬߬�Ѭ�ڬ�
	if (!comment.isEmpty())
		zip.setComment(comment);
	zip.close();
	if (zip.getZipError() != 0) {
		myMessageOutput(true, QtDebugMsg, QString("testCreate(): zip.close(): %1").arg(zip.getZipError()));
		return false;
	}
	return true;
}
