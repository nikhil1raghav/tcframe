#pragma once

#include <set>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "tcframe/spec/exception.hpp"

using std::pair;
using std::set;
using std::string;
using std::tie;
using std::vector;

namespace tcframe {

struct MultipleTestCasesConstraintsVerificationResult {
private:
    set<string> unsatisfiedConstraintDescriptions_;

public:
    MultipleTestCasesConstraintsVerificationResult(const set<string>& unsatisfiedConstraintDescriptions)
            : unsatisfiedConstraintDescriptions_(unsatisfiedConstraintDescriptions) {}

    MultipleTestCasesConstraintsVerificationResult() {}

    const set<string>& unsatisfiedConstraintDescriptions() const {
        return unsatisfiedConstraintDescriptions_;
    }

    bool isValid() const {
        return unsatisfiedConstraintDescriptions_.empty();
    }

    bool operator==(const MultipleTestCasesConstraintsVerificationResult& o) const {
        return tie(unsatisfiedConstraintDescriptions_) == tie(o.unsatisfiedConstraintDescriptions_);
    }

    FormattedError asFormattedError() const {
        vector<pair<int, string>> messages;
        messages.emplace_back(0, "Does not satisfy constraints, on:");
        for (const string& unsatisfiedConstraintDescription : unsatisfiedConstraintDescriptions_) {
            messages.emplace_back(1, unsatisfiedConstraintDescription);
        }
        return FormattedError(messages);
    }
};

}