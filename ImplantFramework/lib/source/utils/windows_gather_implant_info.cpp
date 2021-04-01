/** @file windows_gather_system_info.cpp
 * @brief Defines the functions needed to gather system information.
 * @author f1rehaz4rd
 */

#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <windows.h>
#include <iphlpapi.h>
#include <winsock2.h>
#include <string>
#include <vector>
#include "gather_implant_info.hpp"

#define WINVERREGISTRYPATH L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"
#define PRODUCTNAMEKEY L"ProductName"
#define RELEASEIDKEY L"ReleaseId"

namespace hivemind_lib {

std::string Gather_Info::GetPrimaryIP() {
  struct in_addr addr{};
  std::string str_ip;

  MIB_TCPTABLE_OWNER_PID *p_tcp_info;
  MIB_TCPROW_OWNER_PID* owner;
  DWORD size;

  SIZE_T first_section_size;
  std::string first_section;
  SIZE_T second_section_size;
  std::string second_section;

  if (GetExtendedTcpTable(
	  nullptr,
	  &size,
	  false,
	  AF_INET,
	  TCP_TABLE_BASIC_CONNECTIONS,
	  0) != ERROR_INSUFFICIENT_BUFFER)
	return "";

  p_tcp_info = (MIB_TCPTABLE_OWNER_PID*)malloc(size);

  if (GetExtendedTcpTable(
	  p_tcp_info,
	  &size,
	  false,
	  AF_INET,
	  TCP_TABLE_BASIC_CONNECTIONS,
	  0) != NO_ERROR)
	return "";

  for (DWORD i = 0; i < p_tcp_info->dwNumEntries; i++) {
	//
	// Get the IP Address
	//
	owner = &p_tcp_info->table[i];

	addr.s_addr = (long)owner->dwLocalAddr;
	str_ip = inet_ntoa(addr);

	//
	// Check if its a valid local address
	//
	first_section_size = str_ip.find(".", 0);
	first_section = str_ip.substr(0, first_section_size);

	if (first_section == "192") {
	  second_section_size = str_ip.find(".", first_section_size + 1);
	  second_section = str_ip.substr(first_section_size + 1,
									 second_section_size - first_section_size - 1);

	  if (second_section == "168")
		break;

	} else if (first_section == "172" || first_section == "10")
	  break;
  }

  return str_ip;
}

std::string Gather_Info::GetHostname() {
  TCHAR hostname[MAX_COMPUTERNAME_LENGTH + 1];
  DWORD hostname_size = sizeof(hostname) / sizeof(hostname[0]);

  if (!GetComputerName(hostname, &hostname_size))
    return "";

  std::string hostname_str = hostname;
  return hostname_str;
}

std::string Gather_Info::GetMACAddr() {
  std::string primary_ip = GetPrimaryIP();
  std::string mac_addr;
  CHAR* mac_char = (char*)malloc(20);

  PIP_ADAPTER_INFO adapter_info;
  ULONG adapter_info_size, status;

  adapter_info = nullptr;

  if ((status = GetAdaptersInfo(NULL, &adapter_info_size))
      != ERROR_BUFFER_OVERFLOW)
    goto Cleanup;

  adapter_info = reinterpret_cast<PIP_ADAPTER_INFO>(malloc(adapter_info_size));
  if (adapter_info == nullptr)
    goto Cleanup;

  if ((status = GetAdaptersInfo(adapter_info, &adapter_info_size))
      != ERROR_SUCCESS)
    goto Cleanup;

  while (adapter_info) {
    if (adapter_info->IpAddressList.IpAddress.String == primary_ip) {
      sprintf_s(mac_char, 20, "%02X:%02X:%02X:%02X:%02X:%02X",
                adapter_info->Address[0], adapter_info->Address[1],
                adapter_info->Address[2], adapter_info->Address[3],
                adapter_info->Address[4], adapter_info->Address[5]);

      mac_addr = mac_char;

      goto Cleanup;
    }

    adapter_info = adapter_info->Next;
  }

Cleanup:
  free(mac_char);

  if (adapter_info)
    free(adapter_info);

  return mac_addr;
}

std::vector<std::string> Gather_Info::GetOtherIPs() {

  std::vector<std::string> ip_list;
  PIP_ADAPTER_INFO adapter_info;
  ULONG adapter_info_size, status;

  adapter_info = nullptr;

  if ((status = GetAdaptersInfo(nullptr, &adapter_info_size))
      != ERROR_BUFFER_OVERFLOW)
    goto Cleanup;

  adapter_info = reinterpret_cast<PIP_ADAPTER_INFO>(malloc(adapter_info_size));
  if (adapter_info == nullptr)
    goto Cleanup;

  if ((status = GetAdaptersInfo(adapter_info, &adapter_info_size))
      != ERROR_SUCCESS)
    goto Cleanup;

  while (adapter_info) {
    if (strncmp(adapter_info->IpAddressList.IpAddress.String, "0.0.0.0", 7) != 0) {
      ip_list.push_back(adapter_info->IpAddressList.IpAddress.String);
    }
    adapter_info = adapter_info->Next;
  }

Cleanup:
  if (adapter_info)
    free(adapter_info);

  return ip_list;
}

};
