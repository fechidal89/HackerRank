/** Includes **/
#include <iostream>
#include <sstream>
#include <map>
#include <stack>
#include <vector>

/** Forward declarations **/
class Node;

/** Defines **/
typedef std::map<std::string, Node*>       Tree;
typedef std::map<std::string, std::string> Attributes;

class Node
{
  public:

    Node()
    : parent(nullptr)
    {
    }

  public:

    std::string tag;
    Node*       parent;
    Tree        children;
    Attributes  attributes;
};

/** Static Functions **/
std::vector<std::string> splitLine(const std::string& line, const char separator);
std::string removeSymbols(const std::string& str);
size_t      readSizeT(std::istringstream& stream);
Tree        readXml(size_t lines);
void        doQueries(const Tree& root, size_t queries);

/** Main Function **/
int main()
{
  std::string line;
  std::getline(std::cin, line);

  std::istringstream sstream(line);
  size_t             lines   = readSizeT(sstream);
  size_t             queries = readSizeT(sstream);

  doQueries(readXml(lines), queries);

  return 0;
}

size_t
readSizeT(std::istringstream& stream)
{
  size_t value;
  stream >> value;
  return value;
}

Tree
readXml(size_t lines) // Remember that can be nodes isolates... <tag1></tag1><tag2></tag2>
{
  Tree  root;
  Node* parent = nullptr;
  std::stack<std::string> tags;

  for (size_t i = 0; i < lines; ++i)
  {
    std::string line;
    std::getline(std::cin, line);
    line = removeSymbols(line);
    std::cout << line << std::endl;
    std::vector<std::string> words = splitLine(line, ' ');

    if (words.size() == 1 && words[0].find("/") != std::string::npos)
    {
      std::cout << "Found a Close tag: " << tags.top() << std::endl;
      tags.pop();
      parent = parent->parent;
    }
    else
    {
      Node*       child   = new Node();
      std::string tagName = words[0];

      if (tags.empty())
      {
        child->parent = nullptr;
        child->tag    = tagName;
        root[tagName] = child;
        parent = child;
      }
      else
      {
        child->parent = parent;

      }

      tags.push(tagName);

      if (words.size() == 1)
      {
        std::cout << "Found a Open tag: " << tagName << std::endl;
      }
      else
      {
        std::cout << "Found a Open tag: " << tagName << " with attributes..." <<std::endl;
      }

    }
  }

  return root;
}

void
doQueries(const Tree& root, size_t queries)
{ //std::cout << "--- Queries ---" << std::endl;
  std::string line;

  for (size_t i = 0; i < queries; ++i)
  {
    std::getline(std::cin, line);
    //std::cout << line << std::endl;
  }
}

std::string
removeSymbols(const std::string& str)
{
  std::string result;
  size_t startPos = str.find_first_not_of("<");
  size_t endPos   = str.find_last_not_of(">");

  result = str.substr(0, endPos + 1);
  result = result.substr(startPos);

  return result;
}

std::vector<std::string>
splitLine(const std::string& line, const char separator )
{
  std::string              str;
  std::vector<std::string> strings;
  std::istringstream       sstream(line);

  while (std::getline(sstream, str, separator))
    strings.push_back(str);

  return strings;
}
