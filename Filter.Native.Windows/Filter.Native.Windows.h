#pragma once

#include "ConflictReason.h"

using namespace System;
using namespace System::Collections::Generic;

int SearchConflictReason(int** arr);

namespace FilterNativeWindows {
	public ref class ConflictDetection
	{
    public:
        static List<ConflictReason>^ SearchConflictReason();

	};
}
