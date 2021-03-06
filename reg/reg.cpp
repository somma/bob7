
#include "stdafx.h"
#include "log.h"
#include "RegistryUtil.h"


bool
reg_key_callback(
	_In_ uint32_t index,
	_In_ const wchar_t* base_name,
	_In_ const wchar_t* sub_key_name,
	_In_ const wchar_t* class_name,
	_In_ DWORD_PTR tag
	)
{
	UNREFERENCED_PARAMETER(base_name);
	UNREFERENCED_PARAMETER(tag);

	log_dbg
		"index = %u, sub_key_name = %ws",
		index, sub_key_name
		log_end;
	return true;
}

//bool
//reg_value_callback(
//	_In_ uint32_t index,
//	_In_ uint32_t value_type,
//	_In_ const wchar_t* value_name,
//	_In_ uint32_t value_data_size,
//	_In_ const uint8_t* value_data,
//	_In_ DWORD_PTR tag
//	)
//{
//	UNREFERENCED_PARAMETER(index);
//	UNREFERENCED_PARAMETER(value_type);
//	UNREFERENCED_PARAMETER(value_data_size);
//	UNREFERENCED_PARAMETER(value_data);
//	UNREFERENCED_PARAMETER(tag);
//
//	log_dbg
//		"value name=%ws",
//		value_name
//		log_end;
//
//	return true;
//}


int main()
{
	//
	//	Initialize log 
	//
	initialize_log(0xffffffff, log_level_debug, log_to_con | log_to_file, L"c:\\dbg\\log.txt");
	

	//
	//	Enumerate keys under Software
	//

	//// Computer\HKEY_LOCAL_MACHINE\SOFTWARE
	//HKEY key = RUOpenKey(HKEY_LOCAL_MACHINE, L"SOFTWARE", true);
	//if (NULL == key)
	//{
	//	log_err "RUOpenKey( HKLM\\SYSTEM\\SOFTWARE) failed." log_end;
	//	return false;
	//}

	//reg_enum_key_values(key,
	//					nullptr,
	//					reg_key_callback,
	//					NULL,
	//					nullptr, //reg_value_callback,
	//					NULL);
	//RegCloseKey(key);

	//log_err "Press any key to terminate..." log_end;
	//_pause;


	//
	//	Basic registry key create, open, read, write, delete
	//
	// Create key	
	HKEY key = RUCreateKey(HKEY_CURRENT_USER, L"_test_key", false);
	if (NULL == key) return false;
	RegCloseKey(key);

	// key created ?
	if (true != RUIsKeyExists(HKEY_CURRENT_USER, L"_test_key")) return false;

	// write dword value 
	key = RUOpenKey(HKEY_CURRENT_USER, L"_test_key", false);
	_ASSERTE(nullptr != key);
	_ASSERTE(true == RUWriteDword(key, L"TestValue", 1000));

	// write string 
	_ASSERTE(true == RUSetString(key, L"TestValueString", L"abc"));

	_pause;


	// read dword value 
	_ASSERTE(1000 == RUReadDword(key, L"TestValue", 0));

	std::wstring str;
	_ASSERTE(true == RUReadString(key, L"TestValueString", str));
	_ASSERTE(0 == str.compare(L"abc"));

	// Delete DWORD Value
	_ASSERTE(true == RUDeleteValue(key, L"TestValue"));

	// Delete key
	// -- key 내부의 value 들도 함께 삭제됨
	_ASSERTE(true == RUDeleteKey(HKEY_CURRENT_USER, L"_test_key", true));


	finalize_log();
	return true;
}

