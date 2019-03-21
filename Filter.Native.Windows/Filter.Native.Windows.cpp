#include "stdafx.h"

#include "Filter.Native.Windows.h"

#include <cstddef>

namespace FilterNativeWindows {
    List<ConflictReason>^ ConflictDetection::SearchConflictReason() {
        int* arr = nullptr;
        int arrLen = ::SearchConflictReason(&arr);

        if (arrLen == 0) {
            return nullptr;
        }
        else {
            List<ConflictReason>^ list = gcnew List<ConflictReason>(arrLen);

            for (int i = 0; i < arrLen; i++) {
                list->Add((ConflictReason)arr[i]);
            }

            return list;
        }
    }
}
