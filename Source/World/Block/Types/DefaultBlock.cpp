#include "DefaultBlock.h"

#include "../../World.h"

DefaultBlock::DefaultBlock(std::string&& dataFileName)
:   BlockType (std::move(dataFileName))
{}


