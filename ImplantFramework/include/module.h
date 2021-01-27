#include <map>
#include <string>
#include <vector>

namespace hivemind {
	/**
	 * @brief Struct used to describe parameters needed for a given function in a module.
	*/
	struct ModuleFuncParamInfo {
		std::string paramName;
		std::string paramType;
	};

	/**
	 * @brief Struct used to describe a callable function in this module.
	*/
	struct ModuleFuncInfo{
		std::string moduleFuncName;
		std::string moduleDesc;
		int paramNum;
		std::vector<ModuleFuncParamInfo> paramInfos;
	};

	/**
	 * @brief Struct to describe a module.
	*/
	struct ModuleInfo {
		std::string moduleName;
		std::string moduleDesc;
		std::vector<ModuleFuncInfo> moduleFuncs;
	};

	/**
	 * @brief Abstract class for modules. Forces certain variables and function to be created.
	*/
	class Module {
	public:
		std::map<std::string, void*> funcMap;
		std::map<std::string, int> timeoutMap;
		ModuleInfo modInfo;

		/**
		 * @brief Fill in the funcMap with function names and pointers to the functions.
		 *		  Fill in timeoutMap with function names and values in seconds elapsed for which the function should be terminated. 
		 * @return modInfo completely filled out.
		*/
		virtual ModuleInfo init() = 0;
	}; 
}