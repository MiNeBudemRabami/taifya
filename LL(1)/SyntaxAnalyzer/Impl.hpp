#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#include "../../Lexer/LexerLib/Lexer.hpp"

struct InputTableData
{
	size_t number = 0;
	std::string symbol;
	std::vector<std::string> guideCharacters;
	bool isShift = false;
	bool isError = true;
	size_t pointer = 0;
	bool isStack = false;
	bool isEnd = false;
};

enum class Action
{
	Add,
	Delete
};

struct OutputTableData
{
	size_t number;
	Action action;
	size_t stackItem;
	std::string currentSymbol;
};

using PairStringString = std::pair<std::string, std::string>;

const std::string TAB = "\t";
const std::string END_CHAIN = "$";

std::string PrecariousLexemeTypeToString(LexemeType type)
{
	if (type == LexemeType::EndOfFile)
	{
		return END_CHAIN;
	}
	return LexemeTypeToString(type);
}

std::string ActionToString(Action action)
{
	switch (action)
	{
	case Action::Add:
		return "Add";
	case Action::Delete:
		return "Delete";
	default:
		throw std::exception("Unknown action");
	}
}

std::string GetString(std::istringstream& iss)
{
	std::string str;
	iss >> str;
	return str;
}

int ParseNumber(std::string str)
{
	try
	{
		return std::stoi(str);
	}
	catch (const std::exception&)
	{
		throw std::invalid_argument("Not an int value: " + str);
	}
}

bool BoolToInt(int num)
{
	if (num == 0)
	{
		return false;
	}
	else if (num == 1)
	{
		return true;
	}
	else
	{
		throw std::exception(std::string("Not a bool value: " + std::to_string(num)).c_str());
	}
}

std::vector<std::string> GetFillVector(std::istringstream& iss)
{
	std::vector<std::string> res;
	std::string str;
	while (iss >> str)
	{
		res.push_back(str);
	}
	return res;
}

bool InitBoolVariable(std::istringstream& iss)
{
	return BoolToInt(ParseNumber(GetString(iss)));
}

void InitInputTable(std::ifstream& fileTableInput, std::vector<InputTableData>& inputTable)
{
	std::string line;
	std::getline(fileTableInput, line);

	while (std::getline(fileTableInput, line))
	{
		std::istringstream iss(line);

		InputTableData inputData;
		inputData.number = ParseNumber(GetString(iss));
		inputData.isShift = InitBoolVariable(iss);
		inputData.isError = InitBoolVariable(iss);
		inputData.pointer = ParseNumber(GetString(iss));
		inputData.isStack = InitBoolVariable(iss);
		inputData.isEnd = InitBoolVariable(iss);
		inputData.symbol = GetString(iss);
		inputData.guideCharacters = GetFillVector(iss);

		inputTable.push_back(inputData);
	}
}

bool HaveSymbolInGuide(const std::vector<std::string>& guideCharacters, const std::string symbol)
{
	return std::find(guideCharacters.begin(), guideCharacters.end(), symbol) != guideCharacters.end();
}

InputTableData GetInputDataBySymbolAndCurrentSymbol(const std::vector<InputTableData>& inputTable, std::string symbol, std::string currentSymbol)
{
	if (auto it = std::find_if(inputTable.cbegin(), inputTable.cend(), [&](const InputTableData& data) { // TODO: uncomment in case of emergency
			return (data.symbol == symbol) && HaveSymbolInGuide(data.guideCharacters, currentSymbol);
			// return (data.symbol == symbol) && (HaveSymbolInGuide(data.guideCharacters, currentSymbol) || HaveSymbolInGuide(data.guideCharacters, END_CHAIN));
		}); it != inputTable.cend())
	{
		return *it;
	}
	throw std::invalid_argument("Error. Wrong character: " + currentSymbol);
}

InputTableData GetNewInputData(const std::vector<InputTableData>& inputTable, std::string currentSymbol, size_t pointer, bool isEnd)
{
	if (auto it = std::find_if(inputTable.cbegin(), inputTable.cend(), [&](const InputTableData& data) {
			return data.number == pointer;
		}); it != inputTable.cend())
	{
		InputTableData result = *it;

		// TODO:
		std::string str = (isEnd && !result.isError) ? PrecariousLexemeTypeToString(LexemeType::EndOfFile) : currentSymbol;
		// std::string str = (isEnd && !result.isError) ? END_CHAIN : currentSymbol;

		if (!HaveSymbolInGuide(result.guideCharacters, str) && result.pointer != 0)
		{
			result = GetInputDataBySymbolAndCurrentSymbol(inputTable, result.symbol, str);
		}
		return result;
	}
	throw std::exception("Error. Not find in input table number");
}

void RecursiveMethod(const std::vector<InputTableData>& inputTable, std::vector<OutputTableData>& outputTable, std::stack<size_t>& stack,
	const InputTableData& inputData, const std::vector<Lexeme>& lexemes, size_t& index, bool isEnd)
{
	std::cout << "we are now at " << inputData.number << " position" << "\n";

	

	if (inputData.isEnd && stack.empty())
	{
		return;
	}

	size_t nextIndex = index + 1;

	if (inputData.isShift && nextIndex < lexemes.size())
	{
		++index;
	}

	if (nextIndex >= lexemes.size())
	{
		isEnd = true;
	}

	// TODO:
	std::string currentSymbol = PrecariousLexemeTypeToString(lexemes[index].type);
	// std::string currentSymbol = lexemes[index].lexeme;

	if (inputData.isStack)
	{
		size_t stackItem = inputData.number + 1;
		outputTable.push_back({ inputData.number, Action::Add, stackItem, currentSymbol });
		stack.push(stackItem);

		InputTableData newInputData = GetNewInputData(inputTable, currentSymbol, inputData.pointer, isEnd);
		RecursiveMethod(inputTable, outputTable, stack, newInputData, lexemes, index, isEnd);
	}
	else
	{
		if (inputData.pointer == 0)
		{
			if (stack.empty())
			{
				throw std::runtime_error("Error. Empty stack");
			}

			size_t pointer = stack.top();
			stack.pop();
			outputTable.push_back({ inputData.number, Action::Delete, pointer, currentSymbol });

			InputTableData newInputData = GetNewInputData(inputTable, currentSymbol, pointer, isEnd);
			RecursiveMethod(inputTable, outputTable, stack, newInputData, lexemes, index, isEnd);
		}
		else
		{
			InputTableData newInputData = GetNewInputData(inputTable, currentSymbol, inputData.pointer, isEnd);
			RecursiveMethod(inputTable, outputTable, stack, newInputData, lexemes, index, isEnd);
		}
	}
}

void MakeProcess(std::vector<InputTableData>& inputTable, std::vector<OutputTableData>& outputTable, const std::vector<Lexeme>& lexemes)
{
	if (lexemes.empty())
	{
		throw std::exception("Empty lexemes vector");
	}

	std::stack<size_t> stack;
	size_t index = 0;

	// TODO:
	InputTableData resut = GetInputDataBySymbolAndCurrentSymbol(inputTable, inputTable.front().symbol, PrecariousLexemeTypeToString(lexemes.front().type));
	// InputTableData resut = GetInputDataBySymbolAndCurrentSymbol(inputTable, inputTable.front().symbol, lexemes.front().lexeme);
	RecursiveMethod(inputTable, outputTable, stack, resut, lexemes, index, false);

	if (index != (lexemes.size() - 1))
	{
		throw std::exception("Unprocessed lexemes in sentence");
	}

	std::cout << "Stack is empty. Well done!" << std::endl;
}

void PrintResult(std::ostream& output, const std::vector<OutputTableData>& outputTable)
{
	output << "Number" << TAB << "Action" << TAB << "Stack" << TAB << "CurrentSymbol" << std::endl;

	for (size_t i = 0; i < outputTable.size(); ++i)
	{
		OutputTableData outputData = outputTable[i];
		output << outputData.number << TAB << ActionToString(outputData.action) << TAB << outputData.stackItem << TAB << outputData.currentSymbol << std::endl;
	}
}
