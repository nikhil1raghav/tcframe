#include "gmock/gmock.h"

#include <ostream>
#include <sstream>

#include "tcframe/io/LineIOSegment.hpp"
#include "tcframe/io/LineIOSegmentPrinter.hpp"
#include "tcframe/io/WhitespacePrinter.hpp"
#include "tcframe/type/Scalar.hpp"

#include "../type/MockScalar.hpp"
#include "MockWhitespacePrinter.hpp"

using ::testing::InSequence;
using ::testing::NiceMock;
using ::testing::Test;

using std::ostream;
using std::ostringstream;

namespace tcframe {

class LineIOSegmentPrinterTests : public Test {
protected:
    NiceMock<MockScalar> scalarA;
    NiceMock<MockScalar> scalarB;
    NiceMock<MockScalar> scalarC;
    NiceMock<MockWhitespacePrinter> whitespacePrinter;
    ostream* out;

    LineIOSegmentPrinter printer;

    LineIOSegmentPrinterTests()
            : out(new ostringstream())
            , printer(&whitespacePrinter)
    {}
};

TEST_F(LineIOSegmentPrinterTests, Scalars) {
    LineIOSegment* segment = LineIOSegmentBuilder()
            .addScalarVariable(&scalarA)
            .addScalarVariable(&scalarB)
            .addScalarVariable(&scalarC)
            .build();

    {
        InSequence sequence;
        EXPECT_CALL(scalarA, printTo(out));
        EXPECT_CALL(whitespacePrinter, printSpace(out))
                .RetiresOnSaturation();
        EXPECT_CALL(scalarB, printTo(out));
        EXPECT_CALL(whitespacePrinter, printSpace(out))
                .RetiresOnSaturation();
        EXPECT_CALL(scalarC, printTo(out));
        EXPECT_CALL(whitespacePrinter, printNewline(out));
    }

    printer.print(segment, out);
}

}
