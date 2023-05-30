/*!
\file
\brief https://github.com/gamazov/LabHashingAlgorithm
\author Mazov Grigiriy
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

/*!
\fn void parseStr(std::string input, std::vector<std::string> &output, char sym)
\brief Finds elements separated by the sym symbol in the string str and writes the result to output
\param[in] input The string in which the search is performed
\param[in,out] output Found substrings
\param[in] sym The character by which to divide the string
*/

/*!
\fn void parseNo(Train &train)
\brief Converts the string no to an unsigned number for comparison
\param[in,out] train Structure to be filled in
*/

/*!
\fn void parseData(Train &train)
\brief Converts the data string to an unsigned number for comparison
\param[in,out] train Structure to be filled in
*/

/*!
\fn void parseTime(Train &train)
\brief Converts the string time to an unsigned number for comparison
\param[in,out] train Structure to be filled in
*/

/*!
\fn void parseOnRoad(Train &train)
\brief Converts the string on Road to an unsigned number for comparison
\param[in,out] train Structure to be filled in
*/

/*!
\fn void parseFile(std::vector<Train> &schedules, char *fileName)
\brief All schedule entries are filled in by reading data from the transmitted file
\param[in,out] schedules Schedule to be filled in
\param[in] fileName The file in which the search takes place
*/

/*!
\brief Describes the recording of the train schedule
*/
struct Train {
  //! Departure date
  std::string data;
  //! Departure time
  std::string time;
  //! Train number
  std::string no;
  //! Travel time
  std::string onRoad;
  //! Type of train
  std::string type;

  //! Date represented as an unsigned number for comparison
  unsigned int dataVal = 0;
  //! Departure time, represented as an unsigned number for comparison
  unsigned int timeVal = 0;
  //! A number represented as an unsigned number for comparison
  unsigned int noVal = 0;
  //! Travel time, represented as an unsigned number for comparison
  unsigned int onRoadVal = 0;

  bool operator==(const Train &s) const {
    if (this->data == s.data && this->time == s.time && this->no == s.no && this->onRoad == s.onRoad && this->type == s.type)
      return true;
    return false;
  }
};

void parseFile(std::vector<Train> &schedules, char *fileName);
void parseStr(std::string input, std::vector<std::string> &output, char sym);
void parseNo(Train &train);
void parseData(Train &train);
void parseTime(Train &train);
void parseOnRoad(Train &train);

#ifdef HASH1
/*!
\brief The first hash function
*/
class hash {
public:
  /*!
  \brief The operator of taking a hash from an object
  \param[in] train The object for which the hash is taken
  \return Number - hash of the object
  */
  size_t operator()(const Train &train) const {
    unsigned int result = 0;

    for (size_t i = 0; i < train.data.size(); i++) {
      result += result * 56412 + train.data[i] * (i + 1);
    }

    for (size_t i = 0; i < train.time.size(); i++) {
      result += result * 56412 + train.time[i] * (i + 1);
    }

    for (size_t i = 0; i < train.no.size(); i++) {
      result += result * 56412 + train.no[i] * (i + 1);
    }

    return result;
  }
};
#endif // HASH1

#ifdef HASH2
/*!
\brief The second hash function
*/
class hash {
public:
  /*!
  \brief The operator of taking a hash from an object
  \param[in] train The object for which the hash is taken
  \return Number - hash of the object
  */
  size_t operator()(const Train &train) const {
    unsigned int result = 0;

    for (size_t i = 0; i < train.data.size(); i++) {
      result += ((size_t)train.data[i] << (i % 4) * 8);
    }

    for (size_t i = 0; i < train.time.size(); i++) {
      result ^= ((size_t)train.time[i] << ((i % 4) * 8));
    }

    for (size_t i = 0; i < train.no.size(); i++) {
      result *= ((size_t)train.no[i] << 16);
    }

    for (size_t i = 0; i < train.onRoad.size(); i++) {
      result ^= ((size_t)train.onRoad[i] << ((i % 4) * 8));
    }

    return result;
  }
};
#endif // HASH2

int main(int argc, char *argv[]) {
  if (argc == 1) {
    std::cout << "No parametrs";
    return 1;
  }
    
  std::unordered_set<Train, hash> data;

  std::vector<unsigned int> hashes;
  hash hasher;

  std::vector<Train> schedules;
  parseFile(schedules, argv[1]);

  for (size_t i = 0; i < schedules.size(); i++) {
    size_t hash = hasher(schedules[i]);

    data.insert(schedules[i]);

    bool isInHashes = false;

    for (size_t i = 0; i < hashes.size(); i++) {
      if (hashes[i] == hash) {
        isInHashes = true;
        break;
      }
    }

    if (!isInHashes)
      hashes.push_back(hash);
  }

  int search_index = (int)(rand()) % schedules.size();
  Train search = schedules[search_index];
    
  unsigned int startTime, endTime, searchTime;

  startTime = clock();
  Train finded = *data.find(search);
  endTime = clock();

  searchTime = 1000000.0 * (endTime - startTime) / CLOCKS_PER_SEC;
  std::cout << "Execution time for " << schedules.size() << ": " << searchTime << std::endl;
  std::cout << "Collisions for " << schedules.size() << ": " << schedules.size() - hashes.size() << std::endl;

  return 0;
}

void parseFile(std::vector<Train> &schedules, char *fileName) {
  std::ifstream fin;
  fin.open(fileName);

  char buf[100] = "";
  while (1) {
    fin.getline(buf, 100);
    if (strlen(buf) == 0) {
      break;
    }
    Train train = {};
    std::string str = buf;

    std::vector<std::string> parsedStrs = {};
    parseStr(str, parsedStrs, ' ');
    train.no = parsedStrs[0];
    train.data = parsedStrs[1];
    train.type = parsedStrs[2];
    train.time = parsedStrs[3];
    train.onRoad = parsedStrs[4];

    parseNo(train);
    parseData(train);
    parseTime(train);
    parseOnRoad(train);

    schedules.push_back(train);
  }

  fin.close();
}

void parseStr(std::string input, std::vector<std::string> &output, char sym) {
  unsigned int pos = 0;
  while (input.find(sym, 0) != std::string::npos) {
    pos = input.find(sym, 0);
    output.push_back(input.substr(0, pos));

    input.erase(0, pos + 1);
  }
  output.push_back(input);
}

void parseNo(Train &train) { train.noVal = std::stoi(train.no); }

void parseData(Train &train) {
  std::vector<std::string> parsedStrs = {};
  parseStr(train.data, parsedStrs, '.');

  train.dataVal = 10000 * std::stoi(parsedStrs[2]) + 100 * std::stoi(parsedStrs[1]) + std::stoi(parsedStrs[0]);
}

void parseTime(Train &train) {
  std::vector<std::string> parsedStrs = {};
  parseStr(train.time, parsedStrs, ':');

  train.timeVal = std::stoi(parsedStrs[0] + parsedStrs[1] + parsedStrs[2]);
}

void parseOnRoad(Train &train) {
  std::vector<std::string> parsedStrs = {};
  parseStr(train.onRoad, parsedStrs, ':');

  train.onRoadVal = std::stoi(parsedStrs[0] + parsedStrs[1] + parsedStrs[2]);
}
