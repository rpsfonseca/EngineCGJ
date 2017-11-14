//#include "StringUtils.h"
//
//inline unsigned int findNextChar(unsigned int start, const std::string & str, unsigned int length, char token)
//{
//	unsigned int charFound = start;
//	while (charFound < length)
//	{
//		charFound++;
//		if (str[charFound] == token)
//		{
//			break;
//		}
//	}
//
//	return charFound;
//}
//
//inline std::vector<std::string> splitString(const std::string & str, char delim)
//{
//	std::vector<std::string> elems;
//
//	unsigned int strLength = str.length();
//	unsigned int start = 0;
//	unsigned int end = 0;
//
//	while (end <= strLength)
//	{
//		while (end <= strLength)
//		{
//			if (str[end] == delim)
//			{
//				break;
//			}
//			end++;
//		}
//
//		elems.push_back(str.substr(start, end - start));
//		start = end + 1;
//		end = start;
//	}
//
//	return elems;
//}
