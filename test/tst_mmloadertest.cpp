#include <QString>
#include <QtTest>

class MmMainWindowTest : public QObject
{
    Q_OBJECT

public:
    MmMainWindowTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
};

MmMainWindowTest::MmMainWindowTest()
{
}

void MmMainWindowTest::initTestCase()
{
}

void MmMainWindowTest::cleanupTestCase()
{
}

void MmMainWindowTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(MmMainWindowTest)

#include "tst_mmloadertest.moc"
