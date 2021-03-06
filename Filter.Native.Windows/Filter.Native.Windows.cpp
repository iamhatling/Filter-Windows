#include <cstddef>
#include <Windows.h>

#include <vcclr.h>

#include "Filter.Native.Windows.h"

using namespace System::Diagnostics;

namespace FilterNativeWindows {
    List<ConflictReason>^ ConflictDetection::SearchConflictReason() {
        int* arr = nullptr;
        int arrLen = ::SearchConflictReason(&arr);

        if (arrLen == 0) {
            if (arr != NULL) {
                delete arr;
            }

            return nullptr;
        }
        else {
            List<ConflictReason>^ list = gcnew List<ConflictReason>(arrLen);

            for (int i = 0; i < arrLen; i++) {
                list->Add((ConflictReason)arr[i]);
            }

            delete arr;
            return list;
        }
    }

    int findWinLogonForSession(unsigned int currentSessionId) {
        array<Process^>^ processes = Process::GetProcessesByName("winlogon");
        int i;
        for (i = 0; i < processes->Length; i++) {
            Process^ p = processes[i];
            if ((unsigned int)p->SessionId == currentSessionId) {
                return p->Id;
            }
        }

        return -1;
    }
    
    /// <summary>
    /// Creates a process in elevated mode in the current session.
    /// This will allow CloudVeilInstaller to run in the current session without needing UAC or an IPC client.
    /// </summary>
    /// <param name="filename">The filename.</param>
    /// <param name="arguments">The arguments.</param>
    /// <returns></returns>
    bool ProcessCreation::CreateElevatedProcessInCurrentSession(String^ filename, String^ arguments) {
        if (filename == nullptr) {
            throw gcnew System::NullReferenceException("filename cannot be null.");
        }
        
        if (arguments == nullptr) {
            throw gcnew NullReferenceException("arguments cannot be null");
        }
        
        pin_ptr<const wchar_t> c_filename = PtrToStringChars(filename);
        pin_ptr<const wchar_t> c_arguments = PtrToStringChars(arguments);

        unsigned int currentSessionId = GetActiveSessionId();

        int winlogonPid = findWinLogonForSession(currentSessionId);

        wchar_t* mutable_filename = new wchar_t[wcslen(c_filename) + 1];
        wchar_t* mutable_cmdline = new wchar_t[wcslen(c_arguments) + 1];

        if (mutable_filename == nullptr || mutable_cmdline == nullptr) {
            return false;
        }

        try {
            wcscpy(mutable_filename, c_filename);
            wcscpy(mutable_cmdline, c_arguments);

            int result = ::CreateProcessInCurrentSession(mutable_filename, mutable_cmdline, winlogonPid);

            return result;
        }
        finally{
            if (mutable_filename != nullptr) {
                delete mutable_filename;
}

        if (mutable_cmdline != nullptr) {
            delete mutable_cmdline;
        }
        }

    }
}
