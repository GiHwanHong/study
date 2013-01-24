#include "MainWindow.h"
#include <QtGui>
#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
	: QWidget(parent)
{
	m_tdc.name = "Joonhwan";
	m_tdc.children << "Seyeon"
				<< "Eunseo";
	m_tdc.age = 42;
	m_tdc.level = 5;

	QPushButton* button1 = new QPushButton("Test1");
	connect(button1, SIGNAL(clicked()), SLOT(onClicked()));
	QPushButton* button2 = new QPushButton("Test2");
	connect(button2, SIGNAL(clicked()), SLOT(onClicked2()));

	// - �� ���������� ���� ���� �ݵ�� const T& ������ signal/slot��
	//   �Ǿ�� �Ѵ�.  signal/slot���� Queuedconnection�� �� ���,
	//   ȣ�������� �޴� non-const �������� �ƹ��� �ǹ̰�
	//   ����. ȣ������ ������ ��ü�� ���� ������ �ƴ϶�, ������
	//   ������� ��ü�� ���� ������ �ϱ� �����̴�.

	// enum�� ������ ���� ����� Ÿ�Լ����� ������ �������� �ϸ� �ȴ�.
	qRegisterMetaType<MyEnum::Type>("MyEnum::Type");
	connect(this, SIGNAL(testSignal(const MyEnum::Type&)),
			this, SLOT(testSlot(const MyEnum::Type&)),
			Qt::QueuedConnection);

	// �Ʒ��� ������ qRegisterMetaType()�� ȣ����� ������� �����ϴ�.
	// 1. const ������.
	connect(this, SIGNAL(testSignal2(const TestDataClass&)),
			this, SLOT(testSlot2(const TestDataClass&)));
	// 2a. non-const ������ - Direct
	connect(this, SIGNAL(testSignal2_NonConst(TestDataClass&)),
			this, SLOT(testSlot2_NonConst(TestDataClass&)));
	// 2b. non-const ������ - Queueud
	//  ---> �������� �ʴ´�. �Ʒ��� ���� ��� ���. ������,
	//  qRegisterMetaType<TestDataClass&>("TestDataClass&")�� �������� �ȵȴ�.
	//  ���� �� ���� ����.
	//  QObject::connect: Cannot queue arguments of type 'TestDataClass&'
	// (Make sure 'TestDataClass&' is registered using qRegisterMetaType().)
	//
	// connect(this, SIGNAL(testSignal2_NonConst(TestDataClass&)),
	// 		this, SLOT(testSlot2_NonConst(TestDataClass&)),
	// 		Qt::QueuedConnection);

	// 3. ��������(const �� �ƴϾ �����Ѵ�).
	connect(this, SIGNAL(testSignal3(TestDataClass*)),
			this, SLOT(testSlot_Pointer_Queued(TestDataClass*)),
			Qt::QueuedConnection);

	// �Ʒ��� ������ ó������ ������, testSlot2_Queued()�� �������� �ʴ´�.
	qRegisterMetaType<TestDataClass>("TestDataClass");
	connect(this, SIGNAL(testSignal2(const TestDataClass&)),
			this, SLOT(testSlot2_Queued(const TestDataClass&)),
			Qt::QueuedConnection);

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(button1);
	layout->addWidget(button2);
}

//virtual
MainWindow::~MainWindow()
{
}

void MainWindow::onClicked()
{
	emit testSignal(m_enum);
}

void MainWindow::onClicked2()
{
	// TestDataClass anotherTd;
	// anotherTd = m_tdc;
	emit testSignal2(m_tdc);
	emit testSignal2_NonConst(m_tdc);
	emit testSignal3(&m_tdc);
}

void printResult(const char* func, const void* source, const void* current)
{
	qDebug() << func << ((source==current) ? "������ ��ü" : "������ ��ü");
}

void MainWindow::testSlot(const MyEnum::Type& value)
{
	printResult(__FUNCTION__, &m_enum, &value);
}

void MainWindow::testSlot2(const TestDataClass& tdc)
{
	printResult(__FUNCTION__, &m_tdc, &tdc);
}

void MainWindow::testSlot2_NonConst(TestDataClass& tdc)
{
	printResult(__FUNCTION__, &m_tdc, &tdc);
}

void MainWindow::testSlot2_Queued(const TestDataClass& tdc)
{
	printResult(__FUNCTION__, &m_tdc, &tdc);
}

void MainWindow::testSlot_Pointer_Queued(TestDataClass* tdc)
{
	printResult(__FUNCTION__, &m_tdc, tdc);
}
