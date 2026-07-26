#include "stdafx.h"
#include "patches.hpp"
#include "simplepatternsearcher.hpp"

namespace ChromePatch {
	byte* SimplePatternSearcher::SearchBytePattern(Patch& patch, byte* startAddr, size_t length) {
		for (PatchPattern& pattern : patch.patterns) {
			if (!pattern.pattern.empty() && pattern.pattern[0] == 0xFE && pattern.pattern.size() >= 2) {
				// String XREF Pattern
				size_t strLen = pattern.pattern[1];
				if (pattern.pattern.size() >= 2 + strLen) {
					const char* strData = reinterpret_cast<const char*>(&pattern.pattern[2]);
					byte* strAddr = nullptr;
					
					// Search for string target in current chrome.dll module
					MODULEINFO modInfo{};
					if (GetModuleInformation(GetCurrentProcess(), patches.chromeDll, &modInfo, sizeof(modInfo))) {
						byte* dllBase = reinterpret_cast<byte*>(modInfo.lpBaseOfDll);
						size_t dllSize = modInfo.SizeOfImage;
						for (size_t i = 0; i <= dllSize - strLen; i++) {
							if (memcmp(dllBase + i, strData, strLen) == 0) {
								strAddr = dllBase + i;
								break;
							}
						}
					}

					if (strAddr != nullptr && length >= 7) {
						for (size_t i = 0; i <= length - 7; i++) {
							byte b0 = startAddr[i];
							byte b1 = startAddr[i + 1];
							byte b2 = startAddr[i + 2];
							
							// Check for x64 RIP-relative LEA/MOV (48 8D, 4C 8D, 48 8B, etc. with ModR/M = 0x05 / 0x0D / 0x15 / etc.)
							if ((b0 == 0x48 || b0 == 0x4C || b0 == 0x49) && (b1 == 0x8D || b1 == 0x8B) && ((b2 & 0xC7) == 0x05)) {
								int disp32 = *reinterpret_cast<const int*>(&startAddr[i + 3]);
								uintptr_t targetAddr = reinterpret_cast<uintptr_t>(&startAddr[i]) + 7 + disp32;
								if (targetAddr == reinterpret_cast<uintptr_t>(strAddr)) {
									return &startAddr[i]; // Found instruction referencing target string
								}
							}
						}
					}
				}
				continue;
			}

			for (size_t i = 0; i < length; i++) {
				const byte searchByte = pattern.pattern[pattern.searchOffset];
				if (searchByte == startAddr[i] || searchByte == 0xFF) {
					pattern.searchOffset++;
				} else {
					pattern.searchOffset = 0; // Reset found offsets if the byte differs from the pattern
				}

				if (pattern.searchOffset == pattern.pattern.size()) {
					return startAddr + i - pattern.searchOffset + 1; // Pattern found
				}
			}
		}

		return nullptr;
	}

}
