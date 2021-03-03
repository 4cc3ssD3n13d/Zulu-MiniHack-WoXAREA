bool ComparePattern(DWORD address, DWORD patternAddress, char * mask) {
	int patternLen = strlen(mask);

	for (auto i = 1; i < patternLen; i++) {
		if (mask[i] != *"?" && *(char*)(address + i) != *(char*)(patternAddress + i)) {  // Compare each byte of the pattern with each byte after the current scanning address
			return false;
		}
	}
	if (address != patternAddress) {  // Make sure we aren't returning a match for the pattern defined within your DLLMain
		return true;
	}
	return false;
}

DWORD __patternfind(DWORD patternAddress, char * mask) {
	SYSTEM_INFO sysInfo; // Holds System Information
	GetSystemInfo(&sysInfo);
	DWORD procMin = 0x9000000;  // Minimum memory address of process
	DWORD procMax = 0xfffffff;  // Maximum memory address of process
//	printf("Procmin: %0x \n", procMin);
//	printf("Procmax: %0x \n", procMax);
	MEMORY_BASIC_INFORMATION mBI, mBINext;

	DWORD firstOldProtect = NULL;
	DWORD secondOldProtect = NULL;

	DWORD patternSize = (DWORD)strlen(mask);

	std::vector<DWORD> matches;  // Holds all pattern matches

	while (procMin < procMax) {  // While still scanning memory

		VirtualQueryEx(GetCurrentProcess(), (LPVOID)procMin, &mBI, sizeof(MEMORY_BASIC_INFORMATION));  // Get memory page details

		if ((mBI.State == MEM_COMMIT) && (mBI.Type == MEM_PRIVATE)) {  // Check state of current page

			VirtualProtect((LPVOID)procMin, mBI.RegionSize, PAGE_EXECUTE_READWRITE, &firstOldProtect);  // Set page to read/write/execute

			for (auto n = (DWORD)mBI.BaseAddress; n < (DWORD)mBI.BaseAddress + mBI.RegionSize; n += 0x01) {  // For each byte in this page

				if (n + patternSize > procMax) {  // If our pattern will extend past the maximum memory address, break
					break;
				}

				if (*(char*)n == (*(char*)patternAddress)) {  // If first byte of pattern matches current byte

					if (n + patternSize < (UINT)mBI.BaseAddress + mBI.RegionSize) {  // If entire length of pattern is within this page

						if (ComparePattern((DWORD)n, patternAddress, mask)) {  // Test if full pattern matches
							matches.push_back((DWORD)n);  // If it does, add it to the vector
						}
					}
					else {  // If it isn't within the same page
						VirtualQueryEx(GetCurrentProcess(), (LPVOID)(procMin + mBI.RegionSize), &mBINext, sizeof(MEMORY_BASIC_INFORMATION));  // Same memory page stuff with next page

						if ((mBINext.State == MEM_COMMIT) && (mBINext.Type == MEM_PRIVATE)) {
							VirtualProtect((LPVOID)(procMin + mBI.RegionSize), mBINext.RegionSize, PAGE_EXECUTE_READWRITE, &secondOldProtect);

							if (ComparePattern((DWORD)n, patternAddress, mask)) {
								matches.push_back((DWORD)n);

							}
						}

					}

				}
			}


			VirtualProtect((LPVOID)procMin, mBI.RegionSize, firstOldProtect, NULL);  // Reset memory page state of first page

			if (secondOldProtect) {  // If we scanned into the second page
				VirtualProtect((LPVOID)procMin, mBINext.RegionSize, secondOldProtect, NULL);  // Reset memory page state of second page
				secondOldProtect = NULL;
			}
		}
		procMin += mBI.RegionSize;  // Start scanning next page
	}


	if (!matches.empty()) {
		return matches[0];  // If we had some matches, return the first. -- Change this and return type of functon if you need full list of matches
	}
	else {
		return NULL;  // Return NULL if no matches
	}
}