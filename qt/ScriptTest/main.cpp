// #include "MainWindow.h"
#include <QtGui>
#include <QtScript>
#include "Defect.h"
#include <QDebug>

void printValueStatus(const QString& name, const QScriptValue& value)
{
	qDebug() << "Object:" << name << " --> " << value.toQObject() << endl
			 << "  isValid?:" << value.isValid() << endl
			 << "  isError?:" << value.isError() << endl
			 << "  isNull?:" << value.isNull() << endl
			 << "  isFunction?:" << value.isFunction() << endl
			 << "  isObject?:" << value.isObject() << endl
			 << "  isBool?:" << value.isBool() << endl
			 << "  isNumber?:" << value.isNumber() << endl
		;
}


int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("joonhwan");
	QCoreApplication::setOrganizationDomain("www.joonhwan.org");
	QCoreApplication::setApplicationName("ScriptTest");

	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

	// Step 1 : QScriptEngine ��ü ����
	QScriptEngine engine;

	// Step 2 : ����� C++��ü �� Javascript��ü ����
	DefectObject* defect = new DefectObject(&engine);
	QScriptValue defectObj = engine.newQObject (defect);

	// Step 3 : ���������� Step2 �� ��ü ����
	printValueStatus("defectObj", defectObj);

	// Step 4 : ó���� Javascript �Լ� ���
	//         �Ʒ� ���� ���� ��ü 1���� ���ڷ� ����.
	QScriptValue func = engine.evaluate("(function (defect) {"
										"   if(defect.averageGrayLevel < 12) {"
										"       defect.logDefect(\"hey...\");"
										"       return false;"
										"   }"
										"   return true;"
										"})");
	printValueStatus("func", func);

	QScriptValue badPredicator = engine.globalObject().property("isUknownDefect");
	printValueStatus("isUnknownDefect", badPredicator);

	QScriptValue badResult = badPredicator.call(QScriptValue(), defectObj);
	printValueStatus("badResult", badResult);

	// QScriptValue predicator = engine.globalObject().property("isDummyDefect");
	printValueStatus("predicator", func);

	// Step 4 : ��ϵ� Javascript �Լ� ȣ�� �� ��ȯ�� ����
	QScriptValue result = func.call(QScriptValue(), QScriptValueList() << defectObj);

	printValueStatus("result", result);

	// Step 5 : ��ȯ���� ���� Ȯ��.
	qDebug() << "result is " << result.toBool();

	// MainWindow w;
	// w.show();
	// w.activateWindow();
	// w.raise();
	// return app.exec();
}
