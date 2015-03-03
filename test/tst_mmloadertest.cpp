#include <QString>
#include <QtTest>

class MmLoaderTest : public QObject
{
    Q_OBJECT

public:
    MmLoaderTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
};

MmLoaderTest::MmLoaderTest()
{
}

void MmLoaderTest::initTestCase()
{
}

void MmLoaderTest::cleanupTestCase()
{
}

void MmLoaderTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(MmLoaderTest)

#include "tst_mmloadertest.moc"
