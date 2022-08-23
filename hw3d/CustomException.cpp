#include "CustomException.h"
#include <sstream>

CustomException::CustomException(int line, const char* file) noexcept
	: line(line), file(file)
{

}

const char* CustomException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << '\n'
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

int CustomException::GetLine() const noexcept
{
	return line;
}

const std::string& CustomException::GetFile() const noexcept
{
	return file;
}

std::string CustomException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << '\n'
		<< "[Line] " << line;
}