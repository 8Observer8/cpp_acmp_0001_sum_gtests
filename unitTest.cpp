#include "gtest/gtest.h"

class LogicError : public std::logic_error {
public:

    LogicError( int argument ) : std::logic_error( "" ), m_argument( argument ) {

    }

    virtual const char *what( ) const throw () {
        return m_message.c_str( );
    }

    virtual ~LogicError( ) throw () {

    }

protected:
    int m_argument;
    std::string m_message;
};

class OutOfRange : public LogicError {
public:

    OutOfRange( int argument, int beginOfRange, int endOfRange ) : LogicError( argument ) {
        std::string str_argument, str_beginOfRange, str_endOfRange;

        str_argument = intToString( argument );
        str_beginOfRange = intToString( beginOfRange );
        str_endOfRange = intToString( endOfRange );

        m_message = "Argument " + str_argument + " doesn't hit in the range [" +
                str_beginOfRange + ", " + str_endOfRange + "]";
    }

private:

    std::string intToString( int number ) {
        std::stringstream stream;
        stream << number;
        return stream.str( );
    }
};

int sum( int firstNumber, int secondNumber ) throw (OutOfRange);

TEST( testSum01, normalTest ) {
    int firstNumber = 1;
    int secondNumber = 2;

    int actual = 0;
    ASSERT_NO_THROW({
                        actual = sum( firstNumber, secondNumber );
                    });
    int expected = 3;

    ASSERT_EQ( expected, actual );
}

TEST( testSum02, normalTest ) {
    int firstNumber = 1000000000;
    int secondNumber = 5;

    int actual = 0;
    ASSERT_NO_THROW({
                        actual = sum( firstNumber, secondNumber );
                    });
    int expected = 1000000005;

    ASSERT_EQ( expected, actual );
}

TEST( testSum03, normalTest ) {
    int firstNumber = 5;
    int secondNumber = 1000000000;

    int actual = 0;
    ASSERT_NO_THROW({
                        actual = sum( firstNumber, secondNumber );
                    });
    int expected = 1000000005;

    ASSERT_EQ( expected, actual );
}

TEST( testSum04, normalTest ) {
    int firstNumber = 5;
    int secondNumber = -1000000000;

    int actual = 0;
    ASSERT_NO_THROW({
                        actual = sum( firstNumber, secondNumber );
                    });
    int expected = -999999995;

    ASSERT_EQ( expected, actual );
}

TEST( testSum05, normalTest ) {
    int firstNumber = -1000000000;
    int secondNumber = 5;

    int actual = 0;
    ASSERT_NO_THROW({
                        actual = sum( firstNumber, secondNumber );
                    });
    int expected = -999999995;

    ASSERT_EQ( expected, actual );
}

TEST( testSum06, exceptionTest ) {
    int firstNumber = 5;
    int secondNumber = 1000000001;

    int actual = 0;
    ASSERT_THROW({
                     actual = sum( firstNumber, secondNumber );
                 }, OutOfRange);
}

TEST( testSum07, exceptionTest ) {
    int firstNumber = 1000000001;
    int secondNumber = 5;

    int actual = 0;
    ASSERT_THROW({
                    actual = sum( firstNumber, secondNumber );
                 }, OutOfRange);
}

TEST( testSum08, exceptionTest ) {
    int firstNumber = 5;
    int secondNumber = -1000000001;

    int actual = 0;
    ASSERT_THROW({
                     actual = sum( firstNumber, secondNumber );
                 }, OutOfRange);
}

TEST( testSum09, exceptionTest ) {
    int firstNumber = -1000000001;
    int secondNumber = 5;

    int actual = 0;
    ASSERT_THROW({
                     actual = sum( firstNumber, secondNumber );
                 }, OutOfRange);
}

int main( int argc, char *argv[] ) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS( );
}
