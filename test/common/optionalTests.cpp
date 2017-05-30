#define BOOST_TEST_MODULE optionalTests
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include "TestOptional.h"

#include "asn1cpp/Seq.hpp"
#include "asn1cpp/Getter.hpp"
#include "asn1cpp/Setter.hpp"
#include "asn1cpp/Encoding.hpp"

BOOST_AUTO_TEST_CASE( construction ) {
    auto test = asn1cpp::makeSeq(TestOptional);
}

BOOST_AUTO_TEST_CASE( assignment ) {
    const std::string str = "abcd";
    constexpr unsigned integer = 98;
    constexpr bool boolean = false;

    auto test = asn1cpp::makeSeq(TestOptional);

    asn1cpp::setField(test->string, str);
    asn1cpp::setField(test->integer, integer);
    asn1cpp::setField(test->boolean, boolean);

    bool strOk;
    bool intOk;
    bool boolOk;

    auto vstr = asn1cpp::getField(test->string, std::string, &strOk);
    auto vint = asn1cpp::getField(test->integer, unsigned, &intOk);
    auto vbool = asn1cpp::getField(test->boolean, bool, &boolOk);

    BOOST_CHECK(strOk);
    BOOST_CHECK(intOk);
    BOOST_CHECK(boolOk);

    BOOST_CHECK_EQUAL(str, vstr);
    BOOST_CHECK_EQUAL(integer, vint);
    BOOST_CHECK_EQUAL(boolean, vbool);
}

BOOST_AUTO_TEST_CASE( nonassignment ) {
    auto test = asn1cpp::makeSeq(TestOptional);

    bool strOk;
    bool intOk;
    bool boolOk;

    asn1cpp::getField(test->string, std::string, &strOk);
    asn1cpp::getField(test->integer, unsigned, &intOk);
    asn1cpp::getField(test->boolean, bool, &boolOk);

    BOOST_CHECK(!strOk);
    BOOST_CHECK(!intOk);
    BOOST_CHECK(!boolOk);
}

BOOST_AUTO_TEST_CASE( encoding ) {
    const std::string str = "qwerty";
    constexpr bool boolean = true;

    auto test = asn1cpp::makeSeq(TestOptional);

    asn1cpp::setField(test->string, str);
    asn1cpp::setField(test->boolean, boolean);

    auto encoded = asn1cpp::ber::encode(test);
    auto recoveredTest = asn1cpp::ber::decode(encoded, TestOptional);

    BOOST_CHECK(recoveredTest);

    bool strOk;
    bool intOk;
    bool boolOk;

    auto vstr = asn1cpp::getField(recoveredTest->string, std::string, &strOk);
    asn1cpp::getField(recoveredTest->integer, unsigned, &intOk);
    auto vbool = asn1cpp::getField(recoveredTest->boolean, bool, &boolOk);

    BOOST_CHECK(strOk);
    BOOST_CHECK(!intOk);
    BOOST_CHECK(boolOk);

    BOOST_CHECK_EQUAL(str, vstr);
    BOOST_CHECK_EQUAL(boolean, vbool);
}

BOOST_AUTO_TEST_CASE( copy ) {
    const std::string str = "lkjhgf";
    constexpr unsigned integer = 9571;
    constexpr bool boolean = true;

    auto test = asn1cpp::makeSeq(TestOptional);

    asn1cpp::setField(test->string, str);
    asn1cpp::setField(test->integer, integer);
    asn1cpp::setField(test->boolean, boolean);

    auto copy = test;

    auto vstr = asn1cpp::getField(copy->string, std::string);
    auto vint = asn1cpp::getField(copy->integer, unsigned);
    auto vbool = asn1cpp::getField(copy->boolean, bool);

    BOOST_CHECK_EQUAL(str, vstr);
    BOOST_CHECK_EQUAL(integer, vint);
    BOOST_CHECK_EQUAL(boolean, vbool);
    BOOST_CHECK_EQUAL(test, copy);

    asn1cpp::setField(copy->string, "ooooo");
    BOOST_CHECK(test != copy);
}

BOOST_AUTO_TEST_CASE( clear ) {
    const std::string str = "abcd";
    constexpr unsigned integer = 98;
    constexpr bool boolean = false;

    auto test = asn1cpp::makeSeq(TestOptional);

    asn1cpp::setField(test->string, str);
    asn1cpp::setField(test->integer, integer);
    asn1cpp::setField(test->boolean, boolean);

    bool strOk;
    bool intOk;
    bool boolOk;

    auto vstr = asn1cpp::getField(test->string, std::string, &strOk);
    auto vint = asn1cpp::getField(test->integer, unsigned, &intOk);
    auto vbool = asn1cpp::getField(test->boolean, bool, &boolOk);

    BOOST_CHECK(strOk);
    BOOST_CHECK(intOk);
    BOOST_CHECK(boolOk);

    BOOST_CHECK_EQUAL(str, vstr);
    BOOST_CHECK_EQUAL(integer, vint);
    BOOST_CHECK_EQUAL(boolean, vbool);

    asn1cpp::clrField(test->string, OCTET_STRING);
    asn1cpp::clrField(test->integer, INTEGER);
    asn1cpp::clrField(test->boolean, BOOLEAN);

    asn1cpp::getField(test->string, std::string, &strOk);
    asn1cpp::getField(test->integer, unsigned, &intOk);
    asn1cpp::getField(test->boolean, bool, &boolOk);

    BOOST_CHECK(!strOk);
    BOOST_CHECK(!intOk);
    BOOST_CHECK(!boolOk);
}
